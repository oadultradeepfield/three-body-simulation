#include "integration.h"
#include "bodies.h"
#include <vector>
#include <cmath>

void runge_kutta_step(std::vector<Body>& bodies, double dt) {
    const size_t num_bodies = bodies.size();
    
    std::vector<Body> k1_bodies = bodies;
    std::vector<Body> k2_bodies = bodies;
    std::vector<Body> k3_bodies = bodies;
    std::vector<Body> k4_bodies = bodies;
    
    // First stage (k1)
    for (size_t i = 0; i < num_bodies; ++i) {
        k1_bodies[i].velocity = bodies[i].acceleration(bodies);
    }
    
    // Second stage (k2)
    for (size_t i = 0; i < num_bodies; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            k2_bodies[i].position[j] = bodies[i].position[j] + 0.5 * dt * bodies[i].velocity[j];
            k2_bodies[i].velocity[j] = bodies[i].velocity[j] + 0.5 * dt * k1_bodies[i].velocity[j];
        }
    }
    std::vector<Body> temp_bodies = k2_bodies;
    for (size_t i = 0; i < num_bodies; ++i) {
        k2_bodies[i].velocity = temp_bodies[i].acceleration(temp_bodies);
    }
    
    // Third stage (k3)
    for (size_t i = 0; i < num_bodies; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            k3_bodies[i].position[j] = bodies[i].position[j] + 0.5 * dt * k2_bodies[i].velocity[j];
            k3_bodies[i].velocity[j] = bodies[i].velocity[j] + 0.5 * dt * k2_bodies[i].velocity[j];
        }
    }
    temp_bodies = k3_bodies;
    for (size_t i = 0; i < num_bodies; ++i) {
        k3_bodies[i].velocity = temp_bodies[i].acceleration(temp_bodies);
    }
    
    // Fourth stage (k4)
    for (size_t i = 0; i < num_bodies; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            k4_bodies[i].position[j] = bodies[i].position[j] + dt * k3_bodies[i].velocity[j];
            k4_bodies[i].velocity[j] = bodies[i].velocity[j] + dt * k3_bodies[i].velocity[j];
        }
    }
    temp_bodies = k4_bodies;
    for (size_t i = 0; i < num_bodies; ++i) {
        k4_bodies[i].velocity = temp_bodies[i].acceleration(temp_bodies);
    }
    
    for (size_t i = 0; i < num_bodies; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            bodies[i].position[j] += (dt / 6.0) * (
                bodies[i].velocity[j] + 
                2.0 * k2_bodies[i].velocity[j] + 
                2.0 * k3_bodies[i].velocity[j] + 
                k4_bodies[i].velocity[j]
            );
            bodies[i].velocity[j] += (dt / 6.0) * (
                k1_bodies[i].velocity[j] + 
                2.0 * k2_bodies[i].velocity[j] + 
                2.0 * k3_bodies[i].velocity[j] + 
                k4_bodies[i].velocity[j]
            );
        }
    }
}