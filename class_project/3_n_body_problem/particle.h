#if !defined(PARTICLE_H)
#define PARTICLE_H

#include <math.h>
#include "spatial.h"


struct particle {
    double mass{ 100.0 };  // kg
    spatial position;      // km
    spatial velocity;      // km/s

    double distance(const particle p) {
        return sqrt(pow(p.position.x - this->position.x, 2) + pow(p.position.y - this->position.y, 2) + pow(p.position.z - this->position.z, 2));
    }

    spatial direction(particle p) {
        spatial direction{this->position - p.position};

        double length{ sqrt(abs(direction.x * direction.x) + abs(direction.y * direction.y) + abs(direction.z * direction.z)) };
        direction /= length;

        return direction;
    }
};


#endif
