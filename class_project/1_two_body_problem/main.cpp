/** g++ main.cpp --std=c++17 -o two_body_problem.exe
 *
 * This is the two-body problem in Newtownian physics.
 * The example below is the Hubble Space Telescope (HST)
 * orbiting the Earth.
 */
#include <iostream>
#include <math.h>

const double pi{ 3.1415926535897932384626 };
const double G{ 6.6743e-11 };               // m**3 / (kg * s)
const double C{ 299792458 };                // m / s
const double earth_mass{ 5.9722e24 };       // kg
const double earth_radius{ 6378000.0 };     // m
const double sun_mass{ 1.32712440018e20 };  // kg


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


double gravitational_force(double mass1, double mass2, double dist)
{
    return G * mass1 * mass2 / (dist * dist);
}


double velocity_from_force(double force, int time_delta, double mass)
{
    return (force * time_delta) / mass;
}


double distance(particle p1, particle p2)
{
    return sqrt(pow(p2.position.x - p1.position.x, 2) + pow(p2.position.y - p1.position.y, 2) + pow(p2.position.z - p1.position.z, 2));
}


spatial get_direction(particle p1, particle p2)
{
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


void update_particle(particle *p, spatial direction, double velocity, int time_delta)
{
    p->position.x += p->velocity.x * time_delta + velocity * direction.x / 3.0;
    p->position.y += p->velocity.y * time_delta + velocity * direction.y / 3.0;
    p->position.z += p->velocity.z * time_delta + velocity * direction.z / 3.0;

    p->velocity.x += velocity * direction.x;
    p->velocity.y += velocity * direction.y;
    p->velocity.z += velocity * direction.z;
}


void update_universe(particle *p1, particle *p2, int time_delta)
{
    double dist{ distance(*p1, *p2) };
    double gforce{ gravitational_force(p1->mass, p2->mass, dist) };
    double v1{ velocity_from_force(gforce, time_delta, p1->mass) };
    double v2{ velocity_from_force(gforce, time_delta, p2->mass) };

    spatial direction1to2{ get_direction(*p1, *p2) };
    spatial direction2to1;
    direction2to1.x = -direction1to2.x;
    direction2to1.y = -direction1to2.y;
    direction2to1.z = -direction1to2.z;

    update_particle(p1, direction1to2, v1, time_delta);
    update_particle(p2, direction2to1, v2, time_delta);
}


int main()
{
    // Init Earth
    particle earth;
    earth.mass = earth_mass;
    earth.radius = earth_radius;

    // Init Satelite (HST)
    particle satelite;
    satelite.mass = 11110;
    satelite.radius = 8.2;
    satelite.position.x = 6.9171e6;
    satelite.velocity.y = sqrt(G * earth_mass / satelite.position.x);  // based on stable orbit formula

    double dist{ 1 };
    int t{ 0 };
    int dt{ 1 };

    while(t < 14 * 24 * 60 * 60) {
        update_universe(&earth, &satelite, dt);

        dist = distance(earth, satelite);
        if (std::abs(dist) <= (earth.radius + satelite.radius)){
            std::cout << "BOOM! Collision at time " << t << "\n";
            std::cout << "\tsatelite: (" << satelite.position.x << ", " << satelite.position.y << ", " << satelite.position.z << ")\n";
            std::cout << "\tearth: (" << earth.position.x << ", " << earth.position.y << ", " << earth.position.z << ")\n";
            break;
        } else if ((t % (12 * 60 * 60)) == 0) {
            std::cout << "The satellite is  " << dist<< "  m from Earth at time " << (t / (24 * 60 * 60)) << ".\n";
        }

        t += dt;
    }

    return 0;
}
