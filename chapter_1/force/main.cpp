#include <iostream>

// compiled with: g++ main.cpp --std=c++14 -o force.exe
int main()
{
    double G{ 6.6743e-11 };               // m**3 / (kg * s)
    double earth_mass{ 3.986004418e14 };  // kg
    double earth_radius{ 6378000.0 };      // m
    double your_mass{ 0 };
    std::cout << "How many kg do you weigh?\n";
    std::cin >> your_mass;
    std::cout << "You exert " << G * earth_mass * your_mass / (earth_radius * earth_radius) << " Newtons of force on the Earth.\n";
    return 0;
}
