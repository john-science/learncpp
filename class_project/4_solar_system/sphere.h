#if !defined(SPHERE_H)
#define SPHERE_H

#include <math.h>
#include "spatial.h"


struct sphere {
    double mass{ 100.0 };  // kg
    double radius{ 1.0 };  // km
    spatial position;      // km
    spatial velocity;      // km/s

    double distance(const sphere p) {
        return sqrt(pow(p.position.x - this->position.x, 2) + pow(p.position.y - this->position.y, 2) + pow(p.position.z - this->position.z, 2));
    }

    spatial direction(sphere p) {
        spatial direction{this->position - p.position};

        double length{ sqrt(abs(direction.x * direction.x) + abs(direction.y * direction.y) + abs(direction.z * direction.z)) };
        direction /= length;

        return direction;
    }

    double cross_section() {
        return M_PI * radius * radius;
    }
};


#endif
