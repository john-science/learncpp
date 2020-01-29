// g++ main.cpp --std=c++14 -o stellar_dynamics.exe
#include <iostream>
#include <math.h>

const double pi{ 3.1415926535897932384626 };
const double G{ 6.6743e-11 };               // m**3 / (kg * s)
const double C{ 299792458 };                // m / s
const double earth_mass{ 3.986004418e14 };  // kg
const double earth_radius{ 6378000.0 };     // m
const double sun_mass{ 1.32712440018e20 };  // kg


struct particle {
  double mass{ 100.0 };         // kg
  double position[3] = {0.0, 0.0, 0.0};  // m
  double velocity[3] = {0.0, 0.0, 0.0};;  // m/s
  double radius{ 1.0 };       // m
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
    return sqrt(pow(p2.position[0] - p1.position[0], 2) + pow(p2.position[1] - p1.position[1], 2) + pow(p2.position[2] - p1.position[2], 2));
}


int main()
{
    particle earth;
    earth.mass = earth_mass;
    earth.radius = earth_radius;

    particle satelite;
    satelite.mass = 1000;
    satelite.radius = 5;
    satelite.position[0] = 24e6;
    satelite.velocity[1] = 15e6;

    std::cout << "Distance from Earth to the satelite: " << distance_two_points(earth, satelite) - earth.radius - satelite.radius << "\n";

    return 0;
}
