#include "simulation.h"
#include "bodies.h"
#include "integration.h"
#include "utils.h"
#include <iostream>

void run_simulation(std::vector<Body> &bodies, double dt, double total_time, const std::string &filename, double G)
{
    int steps = total_time / dt;

    for (int i = 0; i < steps; ++i)
    {
        runge_kutta_step(bodies, dt, G);
        print_state(bodies, filename);
    }
}
