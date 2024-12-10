#ifndef BODIES_H
#define BODIES_H

#include <vector>

class Body
{
public:
    double mass;
    std::vector<double> position;
    std::vector<double> velocity;

    Body(double m, std::vector<double> pos, std::vector<double> vel);
    std::vector<double> acceleration(const std::vector<Body> &bodies, double G);
};

#endif
