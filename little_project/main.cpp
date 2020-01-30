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
  spatial position;   // m
  spatial velocity;   // m/s
};



double graviational_force(double m1, double m2, double distance)
{
    return G * m1 * m2 / (distance * distance);
}


double velocity_from_force(double force, double time_delta, double m)
{
    return (force * time_delta) / m;
}


double distance_two_points(particle p1, particle p2)
{
    return sqrt(pow(p2.position.x - p1.position.x, 2) + pow(p2.position.y - p1.position.y, 2) + pow(p2.position.z - p1.position.z, 2));
}


spatial get_direction(particle p1, particle p2)
{
    double dist { distance_two_points(p1, p2) };
    spatial direction;

    direction.x = (p2.position.x - p1.position.x) / dist;
    direction.y = (p2.position.y - p1.position.y) / dist;
    direction.z = (p2.position.z - p1.position.z) / dist;

    return direction;
}


void update_particle(particle p, spatial direction, double velocity, double time_delta) {
    p.velocity.x += velocity * direction.x;
    p.velocity.y += velocity * direction.y;
    p.velocity.z += velocity * direction.z;

    p.position.x += velocity * direction.x * time_delta;
    p.position.y += velocity * direction.y * time_delta;
    p.position.z += velocity * direction.z * time_delta;
}


int main()
{
    particle earth;
    earth.mass = earth_mass;
    earth.radius = earth_radius;

    particle satelite;
    satelite.mass = 1000;
    satelite.radius = 5;
    satelite.position.x = 24e6;
    satelite.velocity.y = 15e6;

    std::cout << "Distance from Earth to the satelite: " << distance_two_points(earth, satelite) - earth.radius - satelite.radius << "\n";

    return 0;
}
