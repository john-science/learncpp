/** g++ main.cpp --std=c++17 -o nbody.exe
 *
 * This is the N-body problem in Newtownian physics.
 * The example below is the Solar System.
 */
#include <iostream>
#include <math.h>
#include <vector>
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
void sum_gravity(std::vector<std::vector<spatial>> gforce, std::vector<spatial> net_gforce);
void update_distances(std::vector<std::vector<double>> dist, std::vector<particle> particles);
void update_gravity(std::vector<spatial> gforce, std::vector<particle> particles,
                    std::vector<std::vector<double>> dist);
void update_particle(particle *p, spatial velocity, int time_delta);
void update_particles(std::vector<particle> particles, std::vector<spatial> velocities, double time_delta);
void update_universe(std::vector<particle> particles, std::vector<std::vector<double>> dist, int time_delta);
spatial velocity_from_force(spatial force, int time_delta, double mass);


/* begin actual program */
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
    // Init Sun
    particle sun;
    sun.mass = sun_mass;

    // TODO: I would like to read this type of data from a text file at run time.

    // Init Earth
    particle earth;
    earth.mass = earth_mass;
    earth.position.x = -2.521092863852298E+10;  // values from: https://ssd.jpl.nasa.gov/horizons.cgi
    earth.position.y = 1.449279195712076E+11;
    earth.position.z = -6.164888475164771E+5;
    earth.velocity.x = -2.983983333368269E+4;
    earth.velocity.y = -5.207633918704476E+3;
    earth.velocity.z = 6.169062303484907E-2;

    // Init Moon
    particle moon;
    moon.mass = moon_mass;
    moon.position.x = -2.552857888050620E+10;
    moon.position.y = 1.446860363961675E+11;
    moon.position.z = 3.593933517466486E+7;
    moon.velocity.x = -2.927904627038706E+4;
    moon.velocity.y = -6.007566180814270E+3;
    moon.velocity.z = -1.577640655646029;

    /* init the array of particless */
    std::vector<particle> particles {sun, earth, moon};
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
            std::cout << "Day  " << (t / day_to_sec) << ": Earth->Sun = " << particles[0].distance(particles[1]) << " m\n";
        }

        t += dt;
    }

    std::cout << "\nEarth location: " << particles[1].position << "\n";
    std::cout << "Earth velocity: " << particles[1].velocity << "\n\n";

    return 0;
}
