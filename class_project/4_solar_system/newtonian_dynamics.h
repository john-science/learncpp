#ifndef NEWTON_DYN_H
#define NEWTON_DYN_H

#include "particle.h"
#include "spatial.h"


double gravitational_force(double mass1, double mass2, double dist);
spatial gravitational_force(particle p1, particle p2, double dist);
void update(int time_delta);
spatial velocity_from_force(spatial force, int time_delta, double mass);


#endif
