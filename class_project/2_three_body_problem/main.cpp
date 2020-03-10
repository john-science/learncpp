/** g++ main.cpp --std=c++17 -o three_body_problem.exe
 *
 * This is the three-body problem in Newtownian physics.
 * The example below is the Sun, Earth, and Earth's Moon.
 */
#include <iostream>
#include <math.h>
#include "scientific_data.h"

/* scientifically meaningful data types */
typedef struct spatial {
  double x { 0 };
  double y { 0 };
  double z { 0 };
} spatial;


typedef struct particle {
  double mass{ 100.0 };  // kg
  double radius{ 1.0 };  // m
  spatial position;      // m
  spatial velocity;      // m/s
  /* TODO: Some particles will be small, and we can skip calculating their graviational forces:
  bool tiny{ false };
  */
} particle;

/* forward declarations */
void calc_net_velocities(spatial velocities[3], spatial gforce[3], int time_delta, particle particles[3]);
double distance(particle p1, particle p2);
spatial get_direction(particle p1, particle p2);
double gravitational_force(double mass1, double mass2, double dist);
spatial gravitational_force(particle p1, particle p2, double dist);
double lambda(double velocity);
void sum_gravity(spatial gforce[3][3], spatial net_gforce[3]);
void update_distances(double dist[3][3], particle particles[3]);
void update_gravity(spatial gforce[3], particle particles[3], double dist[3][3]);
void update_particle(particle *p, spatial *velocity, int time_delta);
void update_particles(particle particles[3], spatial velocities[3], double time_delta);
void update_universe(particle particles[3], double dist[3], int time_delta);
spatial velocity_from_3d_force(spatial force, int time_delta, double mass);
double velocity_from_force(double force, int time_delta, double mass);


/* begin actual program */
spatial gravitational_force(particle p1, particle p2, double dist) {
    spatial force {get_direction(p1, p2)};
    double magnitude{gravitational_force(p1.mass, p2.mass, dist)};

    force.x *= magnitude;
    force.y *= magnitude;
    force.z *= magnitude;

    return force;
}


double gravitational_force(double mass1, double mass2, double dist) {
    return G * mass1 * mass2 / (dist * dist);
}


double velocity_from_force(double force, int time_delta, double mass) {
    return (force * time_delta) / mass;
}


spatial velocity_from_3d_force(spatial force, int time_delta, double mass) {
    spatial velocity;

    velocity.x = velocity_from_force(force.x, time_delta, mass);
    velocity.y = velocity_from_force(force.y, time_delta, mass);
    velocity.z = velocity_from_force(force.z, time_delta, mass);

    return velocity;
}


void calc_net_velocities(spatial velocities[3], spatial gforce[3], int time_delta, particle particles[3]) {
    for (int i=0; i < 3; i++) {
        velocities[i] = velocity_from_3d_force(gforce[i], time_delta, particles[i].mass);
    }
}


double distance(particle p1, particle p2) {
    return sqrt(pow(p2.position.x - p1.position.x, 2) + pow(p2.position.y - p1.position.y, 2) + pow(p2.position.z - p1.position.z, 2));
}


void update_distances(double dist[3][3], particle particles[3]) {
    for (int i=0; i < 3; i++) {
        for (int j=i + 1; j < 3; j++) {
            dist[i][j] = distance(particles[i], particles[j]);
            dist[j][i] = dist[i][j];
        }
    }
}


void update_gravity(spatial gravity[3][3], particle particles[3], double dist[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=i + 1; j < 3; j++) {
            gravity[i][j] = gravitational_force(particles[i], particles[j], dist[i][j]);
            spatial reverse_force;
            reverse_force.x = -(gravity[i][j]).x;
            reverse_force.y = -(gravity[i][j]).y;
            reverse_force.z = -(gravity[i][j]).z;
            gravity[j][i] = reverse_force;
        }
    }
}


void sum_gravity(spatial gforce[3][3], spatial net_gforce[3]) {
    for (int i = 0; i < 3; i++) {
        spatial row;
        for (int j = 0; j < 3; j++) {
            row.x += gforce[i][j].x;
            row.y += gforce[i][j].y;
            row.z += gforce[i][j].z;
        }
        net_gforce[i] = row;
    }
}

spatial get_direction(particle p1, particle p2) {
    spatial direction;
    direction.x = p2.position.x - p1.position.x;
    direction.y = p2.position.y - p1.position.y;
    direction.z = p2.position.z - p1.position.z;

    double total{ abs(direction.x) + abs(direction.y) + abs(direction.z) };

    direction.x /= total;
    direction.y /= total;
    direction.z /= total;

    return direction;
}


void update_particle(particle *p, spatial *velocity, int time_delta) {
    // Divide by 2 because this velocity is the END velocity due to a linear gravitational acceleration.
    p->position.x += p->velocity.x * time_delta + velocity->x * time_delta / 2.0;
    p->position.y += p->velocity.y * time_delta + velocity->y * time_delta / 2.0;
    p->position.z += p->velocity.z * time_delta + velocity->z * time_delta / 2.0;

    p->velocity.x += velocity->x;
    p->velocity.y += velocity->y;
    p->velocity.z += velocity->z;
}

void update_particles(particle particles[3], spatial velocities[3], double time_delta) {
    for (int i=0; i < 3; i++) {
        update_particle(&particles[i], &velocities[i], time_delta);
    }
}


void update_universe(particle particles[3], double dist[3][3], int time_delta) {
    // 0) calc 2D array of distances between particle pairs
    update_distances(dist, particles);

    // 1) calc 2D array of gravitational force between particle pairs
    spatial gforce[3][3];
    update_gravity(gforce, particles, dist);

    // 2) calc 1D array of net directional forces
    spatial net_gforce[3];
    sum_gravity(gforce, net_gforce);

    // 3) calc 1D array of net directional velocities
    spatial velocities[3];
    calc_net_velocities(velocities, net_gforce, time_delta, particles);

    // 4) update all particles with directional velocities
    update_particles(particles, velocities, time_delta);
}


int main() {
    // Init Sun
    particle sun;
    sun.mass = sun_mass;

    // Init Earth
    particle earth;
    earth.mass = earth_mass;
    earth.position.x = earth_sun_mean_dist;
    earth.velocity.y = sqrt(G * sun_mass / earth.position.x);  // based on stable orbit formula

    // Init Moon
    particle moon;
    moon.mass = moon_mass;
    moon.position.x = earth_sun_mean_dist - earth_moon_mean_dist;
    moon.velocity.y = -1 * sqrt(G * earth_mass / earth_moon_mean_dist);  // based on stable orbit formula

    /* init the array of particless */
    particle particles[3] = {sun, earth, moon};

    double dist[3][3] {0};
    double sun_to_earth {0};
    double min_dist { 2 * distance(sun, earth) };
    double max_dist { 0 };

    /* init time and counters for iteration */
    int t{ 0 };
    int dt{ min_to_sec };
    int print_t{ year_to_sec };
    int total_t{ 10 * year_to_sec + 1 };

    while(t < total_t) {
        update_universe(particles, dist, dt);

        sun_to_earth = distance(particles[0], particles[1]);
        if (sun_to_earth < min_dist) {
            min_dist = sun_to_earth;
        } else if (sun_to_earth > min_dist) {
            max_dist = sun_to_earth;
        }

        if ((t % (print_t)) == 0) {
            std::cout << "Day  " << (t / day_to_sec) << ": Earth->Sun = " << sun_to_earth << " m\n";
            //std::cout << "Day  " << (t / day_to_sec) << ": Earth @ " << particles[1].position.x
            //    << ", " << particles[1].position.y << ", " << particles[1].position.z << "\n";
        }

        t += dt;
    }

    cout << "Min distance: " << min_dist << "\n";
    cout << "Max distance: " << max_dist << "\n";

    return 0;
}
