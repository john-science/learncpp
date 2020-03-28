/** A first example reading text from a file.

This example reads a text file where each line represents the data needed to build one struct.
Those structs are loaded into a Vector.
*/
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


// simple struct used to store planet positions
struct Planet{
    std::string name;
    double x, y, z;
};


// helper function to read custom text file 
std::vector<Planet> read_planet_positions_file(std::string file_path) {
    std::vector<Planet> planets;

    std::ifstream infile{file_path};
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

    return planets;
}


int main() {
    std::vector<Planet> planets{read_planet_positions_file("planet_locations.txt")};
    std::cout << "\nX-Position of Planets:\n";
    std::cout << planets[0].name << "\t" << planets[0].x << "\n";
    std::cout << planets[1].name << "\t" << planets[1].x << "\n";
    std::cout << planets[2].name << "\t" << planets[2].x << "\n";
}

