#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include "simulation.h"
#include "bodies.h"
#include "utils.h"
#include "integration.h"

void read_config(const std::string &filename, double &G, double &dt, double &total_time, std::string &output_filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Could not open config file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;

        std::getline(ss, key, '=');
        std::getline(ss, value);

        if (key == "G")
            G = std::stod(value);
        else if (key == "dt")
            dt = std::stod(value);
        else if (key == "total_time")
            total_time = std::stod(value);
        else if (key == "filename")
            output_filename = value;
    }
}

void read_bodies(const std::string &filename, std::vector<Body> &bodies)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Could not open bodies file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    double mass, x, y, z, vx, vy, vz;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);
        if (!(ss >> mass))
        {
            std::cerr << "Invalid mass value in line: " << line << std::endl;
            continue;
        }

        if (!std::getline(file, line) || line.empty() || line[0] == '#')
            continue;
        std::stringstream pos_ss(line);
        if (!(pos_ss >> x >> y >> z))
        {
            std::cerr << "Invalid position values in line: " << line << std::endl;
            continue;
        }

        if (!std::getline(file, line) || line.empty() || line[0] == '#')
            continue;
        std::stringstream vel_ss(line);
        if (!(vel_ss >> vx >> vy >> vz))
        {
            std::cerr << "Invalid velocity values in line: " << line << std::endl;
            continue;
        }

        bodies.push_back(Body(mass, {x, y, z}, {vx, vy, vz}));
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file> <bodies_file>" << std::endl;
        return 1;
    }

    std::string config_filename = argv[1];
    std::string bodies_filename = argv[2];

    double G, dt, total_time;
    std::string output_filename;

    read_config(config_filename, G, dt, total_time, output_filename);

    std::vector<Body> bodies;
    read_bodies(bodies_filename, bodies);

    std::cout << "Simulation started..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    run_simulation(bodies, dt, total_time, output_filename, G);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Simulation completed. Results saved to " << output_filename << std::endl;
    std::cout << "Time taken: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
