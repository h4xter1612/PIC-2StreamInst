#include "particles.hh"
#include <cmath>
#include <random>

Particles::Particles(int N_, double L_) : N(N_), L(L_) {
    x.resize(N);
    v.resize(N);
    beam_id.resize(N);
}

void Particles::initialize_two_stream(double V0, double perturbation, double VT) {
    std::mt19937 gen(0); // Fixed seed for reproducibility
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    for (int i = 0; i < N; i++) {
        x[i] = (L * i) / N;  // posiciones uniformes
        int sign = (i % 2 == 0) ? 1 : -1;
        v[i] = sign * V0 + VT * dis(gen); // Add thermal noise if VT≠0;    // dos corrientes opuestas
        x[i] += perturbation * (L / N) * sign * dis(gen);
        beam_id[i] = sign; // Identificador de haz
    }
}

void Particles::push(double dt, const std::vector<double>& E, double dx) {
    int NG = E.size();
    for (int i = 0; i < N; i++) {
        // Interpolate E field at particle position
        double g = x[i] / dx;
        int g0 = static_cast<int>(g) % NG;
        double frac = g - g0;
        int g1 = (g0 + 1) % NG;
        double E_field = (1 - frac) * E[g0] + frac * E[g1];

        // Update velocity and position
        v[i] += dt * E_field;
        x[i] = fmod(x[i] + v[i] * dt + L, L);
    }
}

