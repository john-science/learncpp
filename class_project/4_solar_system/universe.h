#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <string>
#include <vector>
#include "sphere.h"


class universe {
public:
    // attributes
    double timestamp = 0.0;
    int num_particles = 0;
    std::vector<sphere> particles;
    std::vector<spatial> velocities;
    std::vector<std::vector<double>> dist;

    // constructor
    universe(std::string file_path);

    // methods
    void update(int time_delta);

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
    void update_particle(sphere *p, spatial velocity, int time_delta);
    void update_particles(double time_delta);
};


#endif
