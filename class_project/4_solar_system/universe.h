#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <string>
#include <vector>
#include "sphere.h"


class universe {
public:
    // attributes
    double timestamp = 0.0;
    int num_bodies = 0;
    std::vector<sphere> bodies;
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
    void read_astro_bodies_file(std::string file_path);
    void sum_gravity();
    void update_distances();
    void update_gravity();
    void update_body(sphere *p, spatial velocity, int time_delta);
    void update_bodies(double time_delta);
};


#endif
