// compiled with: g++ main.cpp --std=c++17 -o structs.exe
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


int main() {
    // instantiate your structs
    spatial v1{-3, 1, 0};
    spatial v2{1.5, 2.5, 0.01};

    std::cout << "v1:\t" << v1 << "\n";
    std::cout << "v2:\t" << v2 << "\n\n";

    // call the struct += method to add two structs
    v1 += v2;
    std::cout << "v1+v2:\t" << v1 << "\n\n";

    // call the struct *= method to multiple your coordinates
    v2 *= 100;
    std::cout << "v2*100:\t" << v2 << "\n\n";

    // try out the addition operator
    spatial v3 = v1 + v2;
    std::cout << "v3:\t" << v3 << "\n\n";
}

