// g++ main.cpp --std=c++14 -o stellar.exe
#include <iostream>
#include <math.h>

const double pi{ 3.1415926535897932384626 };
const double G{ 6.6743e-11 };               // m**3 / (kg * s)
const double C{ 299792458 };                // m / s
const double earth_mass{ 3.986004418e14 };  // kg
const double earth_radius{ 6378000.0 };     // m
const double sun_mass{ 1.32712440018e20 };  // kg


struct spatial {
  double x { 0 };
  double y { 0 };
  double z { 0 };
};


struct particle {
  double mass{ 100.0 };  // kg
  double radius{ 1.0 };  // m
  spatial position;      // m
  spatial velocity;      // m/s
};


double gravitational_force(double m1, double m2, double dist)
{
    return G * m1 * m2 / (dist * dist);
}


double velocity_from_force(double force, int time_delta, double m)
{
    return (force * time_delta) / m;
}


double distance(particle p1, particle p2)
{
    return sqrt(pow(p2.position.x - p1.position.x, 2) + pow(p2.position.y - p1.position.y, 2) + pow(p2.position.z - p1.position.z, 2));
}


spatial get_direction(particle p1, particle p2)
{
    double dist { distance(p1, p2) };
    spatial direction;

    direction.x = (p2.position.x - p1.position.x) / dist;
    direction.y = (p2.position.y - p1.position.y) / dist;
    direction.z = (p2.position.z - p1.position.z) / dist;

    return direction;
}


void update_particle(particle &p, spatial direction, double velocity, int time_delta) {
    p.velocity.x += velocity * direction.x;
    p.velocity.y += velocity * direction.y;
    p.velocity.z += velocity * direction.z;

    p.position.x += velocity * direction.x * time_delta;
    p.position.y += velocity * direction.y * time_delta;
    p.position.z += velocity * direction.z * time_delta;
}


void update_universe(particle &p1, particle &p2, int time_delta) {
    double dist{ distance(p1, p2) };
    double gforce{ gravitational_force(p1.mass, p2.mass, dist) };
    double v1{ velocity_from_force(gforce, time_delta, p1.mass) };
    double v2{ velocity_from_force(gforce, time_delta, p2.mass) };
    spatial direction1to2{ get_direction(p1, p2) };
    spatial direction2to1;
    direction2to1.x = -direction1to2.x;
    direction2to1.y = -direction1to2.y;
    direction2to1.z = -direction1to2.z;

    update_particle(p1, direction2to1, v1, time_delta);
    update_particle(p2, direction1to2, v2, time_delta);
}


// TODO: The particle objects are not being updated.
int main()
{
    double dist{ 1 };
    
    // Init Earth
    particle earth;
    earth.mass = earth_mass;
    earth.radius = earth_radius;

    // Init Satelite
    particle satelite;
    satelite.mass = earth_mass / 100;
    satelite.radius = 335;
    satelite.position.x = 24e6;
    satelite.velocity.y = 15e6;

    for (int t=0; t < 100000; t++) {
        update_universe(earth, satelite, 60 * 60);
        
        dist = distance(earth, satelite);
        if (dist <= (earth.radius + satelite.radius)){
            std::cout << "BOOM! Collision at time " << t << "\n";
            break;
        } else if (t % 10000 == 0) {
            std::cout << "The satellite is " << dist<< " meters from Earth at time " << t << ".\n";
            std::cout << "\t" << satelite.position.x << ", " << satelite.position.y << ", " << satelite.position.z << " -- " << gravitational_force(earth.mass, satelite.mass, dist) << "\n";
        }
    }

    return 0;
}
