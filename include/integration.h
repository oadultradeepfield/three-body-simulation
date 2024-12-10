#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include "bodies.h"

void runge_kutta_step(std::vector<Body> &bodies, double dt, double G);

#endif
