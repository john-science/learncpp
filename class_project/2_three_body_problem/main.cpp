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
double gravitational_force(double mass1, double mass2, double dist);
spatial gravitational_force(particle p1, particle p2, double dist);
double velocity_from_force(double force, int time_delta, double mass);
double distance(particle p1, particle p2);
spatial get_direction(particle p1, particle p2);
void update_particle(particle *p, spatial direction, double velocity, int time_delta);
void update_universe(particle *p1, particle *p2, int time_delta);
void update_distances(double dist[3][3], particle particles[3]);


/* begin actual program */
double lambda(double velocity) {
    return 1.0 / sqrt(1.0 - ((velocity * velocity) / (c * c)));
}


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


spatial[3] calc_net_velocities(spatial[3] gforce, int time_delta, particle[3] particles) {
    spatial[3] velocities;

    for (int i=0; i < 3; i++) {
        spatial velocity{ velocity_from_force(gforce[i], time_delta, particles[i]->mass) };
    }

    return velocities;
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


spatial[3][3] update_gravity(particle particles[3], double dist[3][3]) {
    spatial gravity[3][3] = {0};

    for (int i=0; i < 3; i++) {
        for (int j=i + 1; j < 3; j++) {
            gravity[i][j] = gravitational_force(particles[i].mass, particles[j].mass, dist[i][j]);
            spatial reverse_force;
            reverse_force.x = -(gravity[i][j]).x;
            reverse_force.y = -(gravity[i][j]).y;
            reverse_force.z = -(gravity[i][j]).z;
            gravity[j][i] = gravity[i][j];
        }
    }

    return gravity;
}


spatial[3] sum_gravity(spatial[3][3] gforce) {
    spatial tot[3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tot[i].x += gforce[i][j].x;
            tot[i].y += gforce[i][j].y;
            tot[i].z += gforce[i][j].z;
        }
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


void update_particle(particle *p, spatial direction, double velocity, int time_delta) {
    p->position.x += p->velocity.x * time_delta + velocity * direction.x / 3.0;
    p->position.y += p->velocity.y * time_delta + velocity * direction.y / 3.0;
    p->position.z += p->velocity.z * time_delta + velocity * direction.z / 3.0;

    p->velocity.x += velocity * direction.x;
    p->velocity.y += velocity * direction.y;
    p->velocity.z += velocity * direction.z;
}


void update_universe(particle particles[3], double dist[3], int time_delta) {
    // 0) calc 2D array of distances between particle pairs
    update_distances(dist, particles);

    // 1) calc 2D array of gravitational force between particle pairs
    spatial[3][3] gforce{ update_gravity(particles, dist) };

    // 2) calc 1D array of net directional forces
    spatial[3] net_gforce{ sum_gravity(gforce) };

    // 3) calc 1D array of net directional velocities
    spatiel[3] velocities{ calc_net_velocities(net_gforce, time_delta, particles) };

    // 4) update all particles with directional velocities
    update_particle(p1, velocities[0], time_delta);
}


int main() {
    std::cout << "BOOM!\n\nThis is broken!\n\nWork in progress!\n\nDon't expect this to work YET!\n";

    // Init Sun
    particle sun;
    sun.mass = sun_mass;
    sun.radius = sun_radius;

    // Init Earth
    particle earth;
    earth.mass = earth_mass;
    earth.radius = earth_radius;
    earth.position.x = 1.495978707e11;
    satelite.velocity.y = sqrt(G * sun_mass / earth.position.x);  // based on stable orbit formula

    // Init Moon
    particle moon;
    moon.mass = moon_mass;
    moon.radius = moon_radius;
    moon.position.x = earth.position.x + 3.850006e8;
    moon.velocity.y = sqrt(G * earth_mass / moon.position.x);  // based on stable orbit formula

    /* init the array of particless */
    particle particles[3] = {sun, earth, moon};

    double dist[3][3] = {0};

    int t{ 0 };
    int dt{ 60 * 60 };

    while(t < 30 * 24 * 60 * 60) {
        update_universe(particles, dist, dt);

        dist = distance(earth, satelite);
        if ((t % (12 * 60 * 60)) == 0) {
            std::cout << "The satelite is  " << dist<< "  m from Earth at time " << (t / (24 * 60 * 60)) << ".\n";
        }

        t += dt;
    }

    return 0;
}
