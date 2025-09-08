#ifndef PARTICLES_HH
#define PARTICLES_HH

#include <vector>

struct Particles {
    std::vector<double> x;  // posiciones
    std::vector<double> v;  // velocidades
    int N;                  // número de partículas
    double L;               // longitud del dominio

    Particles(int N_, double L_);

    void initialize_two_stream(double V0, double perturbation);
    void push(double dt, const std::vector<double>& E, double dx);
};

#endif

