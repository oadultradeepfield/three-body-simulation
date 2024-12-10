#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>
#include "bodies.h"

void run_simulation(std::vector<Body> &bodies, double dt, double total_time, const std::string &filename, double G);

#endif
