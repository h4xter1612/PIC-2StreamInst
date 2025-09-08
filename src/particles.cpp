#include "particles.hh"
#include <cmath>
#include <random>

Particles::Particles(int N_, double L_) : N(N_), L(L_) {
    x.resize(N);
    v.resize(N);
}

void Particles::initialize_two_stream(double V0, double perturbation) {
    for (int i = 0; i < N; i++) {
        x[i] = (L * i) / N;  // posiciones uniformes
        int sign = (i % 2 == 0) ? 1 : -1;
        v[i] = sign * V0;    // dos corrientes opuestas
        x[i] += perturbation * (L / N) * sign * ((double)rand() / RAND_MAX);
    }
}

void Particles::push(double dt, const std::vector<double>& E, double dx) {
    int NG = E.size();
    for (int i = 0; i < N; i++) {
        int g = static_cast<int>(x[i] / dx) % NG;  // celda en la malla
        double force = E[g];                       // campo local
        v[i] -= dt * force;
        x[i] += dt * v[i];

        // condiciones periódicas
        if (x[i] < 0) x[i] += L;
        if (x[i] >= L) x[i] -= L;
    }
}

