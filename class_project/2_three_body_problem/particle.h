#if !defined(PARTICLE_H)
#define PARTICLE_H


struct particle {
    double mass{ 100.0 };  // kg
    spatial position;      // m
    spatial velocity;      // m/s

    double distance(const particle p) {
        return sqrt(pow(p.position.x - this->position.x, 2) + pow(p.position.y - this->position.y, 2) + pow(p.position.z - this->position.z, 2));
    }
};


#endif
