/** g++ main.cpp --std=c++17 -o nbody.exe
 *
 * This is the N-body problem in Newtownian physics.
 * The example below is the Solar System.
 */
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "scientific_data.h"
#include "spatial.h"
#include "particle.h"

/* forward declarations */
void calc_net_velocities(std::vector<spatial> velocities, std::vector<spatial> gforce, int time_delta,
                         std::vector<particle> particles);
spatial get_direction(particle p1, particle p2);
double gravitational_force(double mass1, double mass2, double dist);
spatial gravitational_force(particle p1, particle p2, double dist);
double lambda(double velocity);
std::vector<particle> read_particle_file(std::string file_path);
void sum_gravity(std::vector<std::vector<spatial>> gforce, std::vector<spatial> net_gforce);
void update_distances(std::vector<std::vector<double>> dist, std::vector<particle> particles);
void update_gravity(std::vector<spatial> gforce, std::vector<particle> particles,
                    std::vector<std::vector<double>> dist);
void update_particle(particle *p, spatial velocity, int time_delta);
void update_particles(std::vector<particle> particles, std::vector<spatial> velocities, double time_delta);
void update_universe(std::vector<particle> particles, std::vector<std::vector<double>> dist, int time_delta);
spatial velocity_from_force(spatial force, int time_delta, double mass);


/* begin actual program */


/** helper function to read custom text file */
std::vector<particle> read_particle_file(std::string file_path) {
    std::vector<particle> particles;

    std::ifstream infile{file_path};
    std::string line;
    std::string name;
    while(std::getline(infile, line))
    {
        if (line[0] == '#' || line.length() < 6) { continue;}

        std::stringstream ss(line);
        particle p;
        if (ss >> name >> p.mass >> p.position.x >> p.position.y >> p.position.z
                                 >> p.velocity.x >> p.velocity.y >> p.velocity.z) {
            particles.push_back(p);
        }
    }

    return particles;
}


spatial gravitational_force(particle p1, particle p2, double dist) {
    spatial force {get_direction(p1, p2)};
    double magnitude{gravitational_force(p1.mass, p2.mass, dist)};

    force *= magnitude;

    return force;
}


double gravitational_force(double mass1, double mass2, double dist) {
    return G * mass1 * mass2 / (dist * dist);
}


spatial velocity_from_force(spatial force, int time_delta, double mass) {
    return force * (time_delta / mass);
}


void calc_net_velocities(std::vector<spatial> velocities, std::vector<spatial> gforce, int time_delta,
                         std::vector<particle> particles) {
    for (int i=0; i < (int)(velocities.size()); i++) {
        velocities[i] = velocity_from_force(gforce[i], time_delta, particles[i].mass);
    }
}


void update_distances(std::vector<std::vector<double>> dist, std::vector<particle> particles) {
    int num_particles{(int)(particles.size())};

    for (int i=0; i < num_particles; i++) {
        for (int j=i + 1; j < num_particles; j++) {
            dist[i][j] = particles[i].distance(particles[j]);
            dist[j][i] = dist[i][j];
        }
    }
}


void update_gravity(std::vector<std::vector<spatial>> gravity, std::vector<particle> particles,
                    std::vector<std::vector<double>> dist) {
    int num_particles{(int)(particles.size())};

    for (int i=0; i < num_particles; i++) {
        for (int j=i + 1; j < num_particles; j++) {
            gravity[i][j] = gravitational_force(particles[i], particles[j], dist[i][j]);
            gravity[j][i] = gravity[i][j] * -1.0;
        }
    }
}


void sum_gravity(std::vector<std::vector<spatial>> gforce, std::vector<spatial> net_gforce) {
    int num_particles{(int)(net_gforce.size())};

    for (int i = 0; i < num_particles; i++) {
        spatial row;
        for (int j = 0; j < num_particles; j++) {
            row += gforce[i][j];
        }
        net_gforce[i] = row;
    }
}

spatial get_direction(particle p1, particle p2) {
    spatial direction;
    direction = p2.position - p1.position;

    double length{ sqrt(abs(direction.x * direction.x) + abs(direction.y * direction.y) + abs(direction.z * direction.z)) };
    direction /= length;

    return direction;
}


void update_particle(particle *p, spatial velocity, int time_delta) {
    // Divide by 3 because this velocity is the END velocity due to a linear gravitational acceleration.
    p->position += p->velocity * time_delta + velocity * (time_delta / 3.0);

    p->velocity += velocity;
}

void update_particles(std::vector<particle> particles, std::vector<spatial> velocities, double time_delta) {
    int num_particles{(int)(particles.size())};

    for (int i=0; i < num_particles; i++) {
        update_particle(&particles[i], velocities[i], time_delta);
    }
}


void update_universe(std::vector<particle> particles, std::vector<std::vector<double>> dist, int time_delta) {
    int num_particles{(int)(particles.size())};

    // 0) calc 2D array of distances between particle pairs
    update_distances(dist, particles);

    // 1) calc 2D array of gravitational force between particle pairs
    std::vector<std::vector<spatial>> gforce(num_particles, std::vector<spatial>(num_particles));
    update_gravity(gforce, particles, dist);

    // 2) calc 1D array of net directional forces
    std::vector<spatial> net_gforce(num_particles);
    sum_gravity(gforce, net_gforce);

    // 3) calc 1D array of net directional velocities
    std::vector<spatial> velocities(num_particles);
    calc_net_velocities(velocities, net_gforce, time_delta, particles);

    // 4) update all particles with directional velocities
    update_particles(particles, velocities, time_delta);
}


// TODO: Create a class for the Universe
int main() {
    /* init the array of particless */
    std::vector<particle> particles {read_particle_file("particle_data.txt")};
    int num_particles = (int)(particles.size());
    std::vector<std::vector<double>> dist(num_particles, std::vector<double>(num_particles, 0));

    /* init time and counters for iteration */
    int t{ 0 };
    int dt{ min_to_sec };
    int print_t{ 30 * day_to_sec };
    int total_t{ year_to_sec };

    std::cout << "\nEarth location: " << particles[1].position << "\n";
    std::cout << "Earth velocity: " << particles[1].velocity << "\n\n";

    while(t < total_t) {
        update_universe(particles, dist, dt);

        if ((t % (print_t)) == 0) {
            std::cout << "Day  " << (t / day_to_sec) << ": Earth->Sun = " << particles[0].distance(particles[1]) << " km\n";
        }

        t += dt;
    }

    std::cout << "\nEarth location: " << particles[1].position << "\n";
    std::cout << "Earth velocity: " << particles[1].velocity << "\n\n";

    return 0;
}
