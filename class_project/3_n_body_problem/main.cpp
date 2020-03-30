/** g++ main.cpp universe.cpp --std=c++17 -o nbody.exe
 *
 * This is the N-body problem in Newtownian physics.
 * The example below is the Solar System.
 */
#include <iostream>
#include "scientific_data.h"
#include "universe.h"


int main() {
    universe u("particle_data.txt");

    /* init time and counters for iteration */
    int t{ 0 };  // TODO: The universe should include the current timestamp (which maybe it should get from the input file)
    int dt{ min_to_sec };
    int print_t{ 30 * day_to_sec };
    int total_t{ year_to_sec };

    /** loop through the time period and occassionally print results */
    std::cout << "\nEarth location: " << u.particles[1].position << "\n";
    std::cout << "Earth velocity: " << u.particles[1].velocity << "\n\n";

    while(t < total_t) {
        u.update(dt);

        if ((t % (print_t)) == 0) {
            std::cout << "Day  " << (t / day_to_sec) << ": Earth->Sun = " << u.particles[0].distance(u.particles[1]) << " km\n";
        }

        t += dt;
    }

    std::cout << "\nEarth location: " << u.particles[1].position << "\n";
    std::cout << "Earth velocity: " << u.particles[1].velocity << "\n\n";

    return 0;
}
