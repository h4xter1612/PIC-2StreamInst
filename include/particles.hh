#ifndef PARTICLES_HH
#define PARTICLES_HH

#include <vector>

struct Particles {
    std::vector<double> x;  // posiciones
    std::vector<double> v;  // velocidades
    int N;                  // número de partículas
    double L;               // longitud del dominio
    std::vector<int> beam_id; // Identificador del haz (1 o -1)

    Particles(int N_, double L_);

    void initialize_two_stream(double V0, double perturbation, double VT);
    void push(double dt, const std::vector<double>& E, double dx);

    const std::vector<int>& get_beam_ids() const { return beam_id; }
};

#endif

