#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "simulation.h"
#include "bodies.h"
#include "utils.h"
#include "integration.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <dt> <total_time> <filename>" << std::endl;
        return 1;
    }

    double dt = std::stod(argv[1]);
    double total_time = std::stod(argv[2]);
    std::string filename = argv[3];

    std::vector<Body> bodies = {
        Body(1.989e30, {0, 0, 0}, {0, 0, 0}), // Sun (Example)
        Body(5.972e24, {1.496e11, 0, 0}, {0, 29783, 0}), // Earth (Example)
        Body(7.348e22, {1.496e11 + 3.844e8, 0, 0}, {0, 29783 + 1022, 0}) // Moon (Example)
    };

    std::cout << "Simulation started..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    run_simulation(bodies, dt, total_time, filename);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Simulation completed. Results saved to " << filename << std::endl;
    std::cout << "Time taken: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
