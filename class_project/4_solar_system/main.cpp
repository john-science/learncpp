/** This is a basic model of the Solar using Newtownian physics.
 *  The example below is the Solar System.
 */
#include <iostream>
#include "physical_data.h"
#include "universe.h"


int main() {
    /** first, create the universe */
    universe u("astronomical_bodies.txt");

    /* init interation counters */
    int dt{ min_to_sec };
    int print_t{ 30 * day_to_sec };
    int total_t{ year_to_sec };

    /** loop through the time period and occassionally print results */
    std::cout << "\nEarth location: " << u.particles[1].position << "\n";
    std::cout << "Earth velocity: " << u.particles[1].velocity << "\n\n";

    while(u.timestamp < total_t) {
        u.update(dt);

        if (((int)(u.timestamp) % (print_t)) == 0) {
            std::cout << "Day  " << (u.timestamp / day_to_sec) << ": Earth->Sun = " << u.dist[0][1] << " km\n";
        }
    }

    std::cout << "\nEarth location: " << u.particles[1].position << "\n";
    std::cout << "Earth velocity: " << u.particles[1].velocity << "\n\n";

    return 0;
}
