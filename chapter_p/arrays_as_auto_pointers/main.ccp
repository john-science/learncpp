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
} particle;


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


int main() {
    particle sun;
    sun.radius = sun_radius;

    particle earth;
    earth.radius = earth_radius;
    earth.position.x = 1.495978707e11;

    particle moon;
    moon.radius = moon_radius;
    moon.position.x = earth.position.x + 3.850006e8;

    particle particles[3] = {sun, earth, moon};
    double dist[3][3] = {0};

    update_distances(dist, particles);

    std::cout << dist[0][0] << '\t' << dist[0][1] << '\t' << dist[0][2] << '\n';
    std::cout << dist[1][0] << '\t' << dist[1][1] << '\t' << dist[1][2] << '\n';
    std::cout << dist[2][0] << '\t' << dist[2][1] << '\t' << dist[2][2] << '\n';

    return 0;
}
