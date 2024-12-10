#include "bodies.h"
#include <vector>

Body::Body(double m, std::vector<double> pos, std::vector<double> vel)
    : position(pos), velocity(vel)
{
    if (m <= 0.0)
    {
        throw std::invalid_argument("Mass must be a positive value");
    }
    mass = m;
}

std::vector<double> Body::acceleration(const std::vector<Body> &bodies, double G = 6.67430e-11)
{
    std::vector<double> accel = {0.0, 0.0, 0.0};
    const double SOFTENING = 1e-8; // avoid division by zeros

    for (const Body &body : bodies)
    {
        if (&body != this)
        {
            double dx = body.position[0] - position[0];
            double dy = body.position[1] - position[1];
            double dz = body.position[2] - position[2];

            double dist_sq = dx * dx + dy * dy + dz * dz + SOFTENING * SOFTENING;
            double dist = sqrt(dist_sq);
            double force = G * mass * body.mass / dist_sq;

            accel[0] += force * dx / (dist * mass);
            accel[1] += force * dy / (dist * mass);
            accel[2] += force * dz / (dist * mass);
        }
    }
    return accel;
}
