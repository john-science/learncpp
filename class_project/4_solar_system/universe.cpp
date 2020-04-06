#include <sstream>
#include <stdexcept>
#include <fstream>
#include "newtonian_dynamics.h"
#include "universe.h"


/** Universe Constructor - This shouldn't take 7 days. */
universe::universe(std::string file_path) {
	// parse the input file with info about all the particles
    read_particle_file(file_path);

    // based on the number of particles, initialize everything else
    num_particles = (int)(particles.size());
    velocities.resize(num_particles);
    net_gforce.resize(num_particles);

    dist.resize(num_particles);
    gforce.resize(num_particles);
    for (int i=0; i < num_particles; i++) {
    	dist[i].resize(num_particles);
    	gforce[i].resize(num_particles);
    }
}


/** build all particles in the system by reading a custom text file */
void universe::read_particle_file(std::string file_path) {
    std::ifstream infile{file_path};
    std::string line;
    std::string name;
    while(std::getline(infile, line))
    {
        if (line[0] == '#' || line.length() < 6) { continue;}

        std::stringstream ss(line);
        particle p;
        if (ss >> name >> p.mass >> p.position.x >> p.position.y >> p.position.z
                                 >> p.velocity.x >> p.velocity.y >> p.velocity.z) {
            particles.push_back(p);
        }
    }

    if (particles.size() < 2) {
        throw std::length_error("Two few particles found in the input file.");
    }
}


/** Sum N directional velocities together to get a net velocity */
void universe::calc_net_velocities(int time_delta) {
    for (int i=0; i < num_particles; i++) {
        velocities[i] = velocity_from_force(net_gforce[i], time_delta, particles[i].mass);
    }
}


/** (Re-)Calculate the Distances between all the particles */
void universe::update_distances() {
    for (int i=0; i < num_particles; i++) {
        for (int j=i + 1; j < num_particles; j++) {
            dist[i][j] = particles[i].distance(particles[j]);
            dist[j][i] = dist[i][j];
        }
    }
}


/** (Re-)Calculate the (directional) gravitational forces between all the pairs of particles */
void universe::update_gravity() {
    for (int i=0; i < num_particles; i++) {
        for (int j=i + 1; j < num_particles; j++) {
            gforce[i][j] = gravitational_force(particles[i], particles[j], dist[i][j]) * -1.0;
            gforce[j][i] = gforce[i][j] * -1.0;
        }
    }
}


/** Sum all the (directional) gravitational forces on one particle */
void universe::sum_gravity() {
    for (int i = 0; i < num_particles; i++) {
        spatial row;
        for (int j = 0; j < num_particles; j++) {
            row += gforce[i][j];
        }
        net_gforce[i] = row;
    }
}


/** Update the position and velocity of a particle, based on it's velocity over a set time interval */
void universe::update_particle(particle *p, spatial velocity, int time_delta) {
    // Divide by 3 because this velocity is the END velocity due to a linear gravitational acceleration.
    p->position += p->velocity * time_delta + velocity * (time_delta / 3.0);

    p->velocity += velocity;
}


/** Update all the particles in the system, given their complete set of velocities */
void universe::update_particles(double time_delta) {
    for (int i=0; i < num_particles; i++) {
        this->update_particle(&particles[i], velocities[i], time_delta);
    }
}


/** Master Method: updates all the particles in system basec on Newtonian dynamics */
void universe::update(int time_delta) {
    // 0) calc 2D array of distances between particle pairs
    this->update_distances();

    // 1) calc 2D array of gravitational force between particle pairs
    this->update_gravity();

    // 2) calc 1D array of net directional forces
    this->sum_gravity();

    // 3) calc 1D array of net directional velocities
    this->calc_net_velocities(time_delta);

    // 4) update all particles with directional velocities
    this->update_particles(time_delta);

    // 5) update the universal timestamp
    timestamp += time_delta;
}
