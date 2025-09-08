# PIC 1D: Two-Stream Instability Simulation

![PIC Simulation](https://img.shields.io/badge/Language-C++17-blue) ![Python](https://img.shields.io/badge/Visualization-Python-green)

---

## Description

This project implements a **1D Particle-in-Cell (PIC)** simulation to model the **two-stream instability** in a plasma.

The code is written in **C++17**, modular, and supports:

- Initialization of two counter-propagating electron streams.  
- Solving the 1D Poisson equation to compute the electric field.  
- Particle push using **Euler method** (position and velocity update).  
- Calculation of **momentum**, **kinetic energy**, **potential energy**, and **total energy** of the system.  
- Exporting data to CSV for analysis and visualization in Python.

The main goal is to study the **time evolution of energy and momentum** and observe the growth of the instability.

---

## Project Structure

PIC2si/
├── include/ # Headers
│ ├── particles.hh
│ ├── fields.hh
│ └── diagnostics.hh
├── src/ # Source files
│ ├── main.cpp
│ ├── particles.cpp
│ ├── fields.cpp
│ └── diagnostics.cpp
├── analysis.py # Python script for visualization
├── CMakeLists.txt
└── README.md


---

## Build

CMake is used to generate and build the project:

mkdir build
cd build
cmake ..
cmake --build . --config Release


The executable will be located in `build/Release/pic1d.exe` (Windows/MSVC) or `build/pic1d` (MinGW/Linux).  

---

## Running the Simulation

Run the simulation to generate the CSV:

./pic1d.exe


This will create `diagnostics.csv` in the same directory as the executable, with columns:

time, momentum, Ekin, Epot, Etotal


---

## Visualization

A Python script `analysis.py` is included to plot:

- Plasma momentum
- Kinetic energy
- Potential energy
- Total energy

Run the script in the same folder as the CSV:

python analysis.py


It will generate a plot showing the temporal evolution of the physical quantities.

---

## Customization

Parameters that can be modified in `main.cpp`:

- `N` : number of super-particles  
- `NG` : number of grid cells  
- `L` : domain length  
- `V0` : initial stream velocity  
- `DT` : time step  
- `NT` : number of time steps  

---

## License

MIT License © 2025 Juan Pablo Solís Ruiz

---

## Contact

- Email: jp.sruiz18.tec@gmail.com  
- GitHub: [h4xter1612](https://github.com/h4xter1612)

