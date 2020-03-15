#if !defined(SPATIAL_H)
#define SPATIAL_H

#include <iostream>


struct spatial {
    double x { 0 };
    double y { 0 };
    double z { 0 };

    spatial operator+(const spatial a) {
	spatial new_s;
        new_s.x = this->x + a.x;
        new_s.y = this->y + a.y;
        new_s.z = this->z + a.z;

        return new_s;
    }

    spatial operator-(const spatial a) {
        spatial new_s;
        new_s.x = this->x - a.x;
        new_s.y = this->y - a.y;
        new_s.z = this->z - a.z;

        return new_s;
    }

    spatial operator+=(const spatial a) {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;

        return *this;
    }

    spatial operator-=(const spatial a) {
        this->x -= a.x;
        this->y -= a.y;
        this->z -= a.z;

        return *this;
    }

    spatial operator*=(const double m) {
        this->x *= m;
        this->y *= m;
        this->z *= m;

        return *this;
    }

    spatial operator/=(const double m) {
        this->x /= m;
        this->y /= m;
        this->z /= m;

        return *this;
    }

};


std::ostream& operator<<(std::ostream& os, const spatial& s) {
    os << '(' << s.x << ", " << s.y << ", " << s.z << ')';
    return os;
}


#endif

