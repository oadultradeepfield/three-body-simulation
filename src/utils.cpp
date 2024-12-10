#include "utils.h"
#include "bodies.h"
#include <iostream>
#include <fstream>
#include <vector>

void print_state(const std::vector<Body> &bodies, const std::string &filename)
{
    std::ofstream output_file(filename, std::ios::app);

    if (!output_file)
    {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    for (const auto &body : bodies)
    {
        output_file << body.position[0] << ", " << body.position[1] << ", " << body.position[2] << "\n";
    }
}
