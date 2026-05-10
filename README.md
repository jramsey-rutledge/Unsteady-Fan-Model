# Unsteady-Fan-Model
This code solves the unsteady advection-diffusion equations for a room with a fan. 

**Author:**
- Jenna Ramsey-Rutledge

## Background



## Physics and Mathematical Model

### Governing Equations
The temperature $T(x,y)$ satisfies the steady advection-diffusion equation written in integral form, 
$$\int_{CS} (\rho c_{p} \vec{u} T) \cdot \vec{n} dA = \int_{CS} k (\nabla T \cdot \vec{n}) dA + \int_{CV} f dV,$$
where $\rho$, $c_p$, and $k$ are the density, specific heat, and theraml conductivity of air, which we assume are constants. The source term $f$ is included for verification purposes and to model a heater. 

### Initial and Boundary Conditions



## Numerical Methods


## Verification

The solver is verified using the Method of Manufactured Solutions. The test solution

$$f = \sin(x)\sin(y)\sin(v_x)\sin(v_y)\sin(t)$$


## Quick Start

### Prerequisites

- C++17-compatible compiler
- GNU Make
- Eigen 5.0.0+

### Building and Running

```bash
# Clone the repository
git clone <repo-url>
cd Unsteady-Fan-Model

# Compile the project
make build

# Run the program
./build/solver.exe

# Remove compiled artifacts
make clean

# Build and run in one step
make all
```

### Adjusting the Simulation

Edit the .inp files in `input/` to change the spatial domain, temporal domain, fan parameters, or physical properties before building


## Project Structure

```
Unsteady-Fan-MOdel/
├── src/                      # Source and header files
│   ├── main.cpp
│   ├── linSysType.{cpp,h}           # Linear solver
│   ├── meshType.{cpp,h}             # Spatial  mesh
│   ├── simTime.{cpp,h}              # Time stepping  
│   ├── volScalarField.{cpp,h}       # Temperature Field
│   ├── bcType.{cpp,h}               # Boundary Conditions
│   ├── fieldVal.{cpp,h}             # Helper structure for Temperature Field
│   ├── surfaceScalarField.{cpp,h}   # Flux
│   ├── velocityField.{cpp,h}        # Fan
│   └── FileIO.{cpp,h}               # Helper structure for reading inputs
├── input/                    # Configuration files
│   ├── controlDict.inp              # Temporal parameters
│   ├── Fan.inp                      # Fan parameters
│   ├── mesh.inp                     # Spatial parameters
│   └── T.inp                        # Physical Properties
├── output/                   # Results and Post-Processing Scripts
│   └── SurfacePlot.m                # Animates Temperature Field in the Room
├── tests /                  # Verification Methods
├── makefile                 # Build configuration
└──README.md                 # This file
```

## References
