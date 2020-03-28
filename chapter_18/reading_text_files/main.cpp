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
        std::cout << "Line:\t" << line << "\n";
        if (line[0] == '#' || line.length() < 4) { continue;}
        std::cout << "\tUsing.\n";
        std::stringstream ss(line);
        Planet planet;
        if (ss >> planet.name >> planet.x >> planet.y >> planet.z) {
            planets.push_back(planet);
        }
    }

    std::cout << "\nX-Position of Planets:\n";
    std::cout << planets[0].name << "\t" << planets[0].x << "\n";
    std::cout << planets[1].name << "\t" << planets[1].x << "\n";
    std::cout << planets[2].name << "\t" << planets[2].x << "\n";
}

