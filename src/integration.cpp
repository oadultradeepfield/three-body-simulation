#include "integration.h"
#include "bodies.h"
#include <vector>
#include <cmath>

void runge_kutta_step(std::vector<Body> &bodies, double dt, double G)
{
    const size_t num_bodies = bodies.size();

    std::vector<std::vector<double>> k1_pos(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k1_vel(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k2_pos(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k2_vel(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k3_pos(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k3_vel(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k4_pos(num_bodies, std::vector<double>(3, 0.0));
    std::vector<std::vector<double>> k4_vel(num_bodies, std::vector<double>(3, 0.0));

    // Calculate k1 (derivatives at the initial state)
    for (size_t i = 0; i < num_bodies; ++i)
    {
        k1_pos[i] = bodies[i].velocity;
        k1_vel[i] = bodies[i].acceleration(bodies, G);
    }

    // Calculate k2 (midpoint using k1)
    std::vector<Body> temp_bodies = bodies;
    for (size_t i = 0; i < num_bodies; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            temp_bodies[i].position[j] += 0.5 * dt * k1_pos[i][j];
            temp_bodies[i].velocity[j] += 0.5 * dt * k1_vel[i][j];
        }
    }
    for (size_t i = 0; i < num_bodies; ++i)
    {
        k2_pos[i] = temp_bodies[i].velocity;
        k2_vel[i] = temp_bodies[i].acceleration(temp_bodies, G);
    }

    // Calculate k3 (midpoint using k2)
    temp_bodies = bodies;
    for (size_t i = 0; i < num_bodies; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            temp_bodies[i].position[j] += 0.5 * dt * k2_pos[i][j];
            temp_bodies[i].velocity[j] += 0.5 * dt * k2_vel[i][j];
        }
    }
    for (size_t i = 0; i < num_bodies; ++i)
    {
        k3_pos[i] = temp_bodies[i].velocity;
        k3_vel[i] = temp_bodies[i].acceleration(temp_bodies, G);
    }

    // Calculate k4 (full step using k3)
    temp_bodies = bodies;
    for (size_t i = 0; i < num_bodies; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            temp_bodies[i].position[j] += dt * k3_pos[i][j];
            temp_bodies[i].velocity[j] += dt * k3_vel[i][j];
        }
    }
    for (size_t i = 0; i < num_bodies; ++i)
    {
        k4_pos[i] = temp_bodies[i].velocity;
        k4_vel[i] = temp_bodies[i].acceleration(temp_bodies, G);
    }

    for (size_t i = 0; i < num_bodies; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            bodies[i].position[j] += (dt / 6.0) * (k1_pos[i][j] + 2.0 * k2_pos[i][j] + 2.0 * k3_pos[i][j] + k4_pos[i][j]);
            bodies[i].velocity[j] += (dt / 6.0) * (k1_vel[i][j] + 2.0 * k2_vel[i][j] + 2.0 * k3_vel[i][j] + k4_vel[i][j]);
        }
    }
}
