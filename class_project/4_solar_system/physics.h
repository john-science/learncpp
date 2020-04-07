#ifndef PHYSICS_H
#define PHYSICS_H

#include "sphere.h"
#include "spatial.h"


double gravitational_force(double mass1, double mass2, double dist);
spatial gravitational_force(sphere p1, sphere p2, double dist);
void update(int time_delta);
spatial velocity_from_force(spatial force, int time_delta, double mass);


#endif
