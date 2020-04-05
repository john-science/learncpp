#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <string>
#include <vector>
#include "particle.h"


class universe {
public:
    // attributes
    double timestamp = 0.0;
    int num_particles = 0;
    std::vector<particle> particles;
    std::vector<spatial> velocities;
    std::vector<std::vector<double>> dist;

    // constructor
    universe(std::string file_path);

    // methods
    double gravitational_force(double mass1, double mass2, double dist);
    spatial gravitational_force(particle p1, particle p2, double dist);
    void update(int time_delta);
    spatial velocity_from_force(spatial force, int time_delta, double mass);

private:
    // attributes
    std::vector<std::vector<spatial>> gforce;
    std::vector<spatial> net_gforce;

    // methods
    void calc_net_velocities(int time_delta);
    void read_particle_file(std::string file_path);
    void sum_gravity();
    void update_distances();
    void update_gravity();
    void update_particle(particle *p, spatial velocity, int time_delta);
    void update_particles(double time_delta);
};


#endif