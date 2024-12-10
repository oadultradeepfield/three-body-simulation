# Three-Body Simulation

💡 _**Future Plan**: Generalize the program for N bodies with a support for spherical coordinates._

A C++ program simulating the motion of three objects under mutual gravitational attraction using Newton's law of gravitation, $F = GMm/r^2$. The simulation approximates the ODE solution with the fourth-order Runge-Kutta method (RK4) to update positions and velocities. Visualization is done using Python's Matplotlib for 3D trajectories and XY projections.

[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=C%2B%2B&logoColor=white)](https://isocpp.org/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=flat&logo=Python&logoColor=white)](https://www.python.org/)

## Installation

1. Clone the repository and navigate to the project directory:

   ```bash
   git clone https://github.com/oadultradeepfield/three-body-simulation.git
   cd three-body-simulation
   ```

2. Create a build directory, generate the Makefile with CMake, and build the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Install Python dependencies for visualization:

   ```bash
   pip install -r python/requirements.txt
   ```

## Usage

1. Configure the simulation by editing `config.txt` and `bodies.txt`:

   - `config.txt`

     ```bash
     G=1
     dt=0.0005
     total_time=50
     filename=results/example_02_eight_shaped_orbit.txt
     ```

   - `bodies.txt`

     ```bash
     # Body 1
     1
     0.97000436 -0.2430875 0.0
     0.466203685 0.4321573 0.0

     # Body 2
     1
     -0.97000436 0.2430875 0.0
     0.466203685 0.4321573 0.0

     # Body 3
     1
     0.0 0.0 0.0
     -0.93240737 -0.8643146 0.0
     ```

2. Run the simulation:

   ```bash
   build/ThreeBodySimulation config.txt bodies.txt
   ```

3. Generate trajectory plots (optional):

   ```bash
   python3 python/plot.py --filename ./results/example_02_eight_shaped_orbit.txt
   ```

The output plot will be saved in the same directory as the `.txt` file.

|                            **Example 3D Trajectory**                            |                             **Example XY Projection**                              |
| :-----------------------------------------------------------------------------: | :--------------------------------------------------------------------------------: |
| ![Example 3D Trajectory](/results/example_02_eight_shaped_orbit_trajectory.png) | ![Example 2D Projection](/results/example_02_eight_shaped_orbit_2d_projection.png) |
