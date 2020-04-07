#include <sstream>
#include <stdexcept>
#include <fstream>
#include "physics.h"
#include "universe.h"


/** Universe Constructor - This shouldn't take 7 days. */
universe::universe(std::string file_path) {
	// parse the input file with info about all the bodies
    read_astro_bodies_file(file_path);

    // based on the number of bodies, initialize everything else
    num_bodies = (int)(bodies.size());
    velocities.resize(num_bodies);
    net_gforce.resize(num_bodies);

    dist.resize(num_bodies);
    gforce.resize(num_bodies);
    for (int i=0; i < num_bodies; i++) {
    	dist[i].resize(num_bodies);
    	gforce[i].resize(num_bodies);
    }
}


/** build all astronomical bodies in the system by reading a custom text file */
void universe::read_astro_bodies_file(std::string file_path) {
    std::ifstream infile{file_path};
    std::string line;
    std::string name;
    while(std::getline(infile, line))
    {
        if (line[0] == '#' || line.length() < 6) { continue;}

        std::stringstream ss(line);
        sphere p;
        if (ss >> name >> p.mass >> p.position.x >> p.position.y >> p.position.z
                                 >> p.velocity.x >> p.velocity.y >> p.velocity.z) {
            bodies.push_back(p);
        }
    }

    if (bodies.size() < 2) {
        throw std::length_error("Two few astronomical bodies found in the input file.");
    }
}


/** Sum N directional velocities together to get a net velocity */
void universe::calc_net_velocities(int time_delta) {
    for (int i=0; i < num_bodies; i++) {
        velocities[i] = velocity_from_force(net_gforce[i], time_delta, bodies[i].mass);
    }
}


/** (Re-)Calculate the Distances between all the bodies */
void universe::update_distances() {
    for (int i=0; i < num_bodies; i++) {
        for (int j=i + 1; j < num_bodies; j++) {
            dist[i][j] = bodies[i].distance(bodies[j]);
            dist[j][i] = dist[i][j];
        }
    }
}


/** (Re-)Calculate the (directional) gravitational forces between all the pairs of bodies */
void universe::update_gravity() {
    for (int i=0; i < num_bodies; i++) {
        for (int j=i + 1; j < num_bodies; j++) {
            gforce[i][j] = gravitational_force(bodies[i], bodies[j], dist[i][j]) * -1.0;
            gforce[j][i] = gforce[i][j] * -1.0;
        }
    }
}


/** Sum all the (directional) gravitational forces on one body */
void universe::sum_gravity() {
    for (int i = 0; i < num_bodies; i++) {
        spatial row;
        for (int j = 0; j < num_bodies; j++) {
            row += gforce[i][j];
        }
        net_gforce[i] = row;
    }
}


/** Update the position and velocity of a sphere, based on it's velocity over a set time interval */
void universe::update_body(sphere *p, spatial velocity, int time_delta) {
    // Divide by 3 because this velocity is the END velocity due to a linear gravitational acceleration.
    p->position += p->velocity * time_delta + velocity * (time_delta / 3.0);

    p->velocity += velocity;
}


/** Update all the bodies in the system, given their complete set of velocities */
void universe::update_bodies(double time_delta) {
    for (int i=0; i < num_bodies; i++) {
        this->update_body(&bodies[i], velocities[i], time_delta);
    }
}


/** Master Method: updates all the bodies in system based on Newtonian dynamics */
void universe::update(int time_delta) {
    // 0) calc 2D array of distances between pairs of bodies
    this->update_distances();

    // 1) calc 2D array of gravitational force between pairs of bodies
    this->update_gravity();

    // 2) calc 1D array of net directional forces
    this->sum_gravity();

    // 3) calc 1D array of net directional velocities
    this->calc_net_velocities(time_delta);

    // 4) update all bodies with directional velocities
    this->update_bodies(time_delta);

    // 5) update the universal timestamp
    timestamp += time_delta;
}
