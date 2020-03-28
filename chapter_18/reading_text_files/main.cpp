#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


struct Planet{
    std::string name;
    double x, y, z;
};


int main() {
    std::vector<Planet> planets;

    std::ifstream infile{"planet_locations.txt"};
    std::string line;
    while(std::getline(infile, line))
    {
        std::cout << "test... " << line << "\n";
        std::stringstream ss(line);
        Planet planet;
        if (ss >> planet.name >> planet.x >> planet.y >> planet.z) {
            planets.push_back(planet);
        }
    }

    std::cout << planets[0].name << "\n";
    std::cout << planets[1].name << "\n";
    std::cout << planets[2].name << "\n";
}

