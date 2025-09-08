#include "fields.hh"
#include <cmath>
#include <algorithm>

Fields::Fields(int NG_, double L_) : NG(NG_), L(L_) {
    dx = L / NG;
    rho.resize(NG, 0.0);
    phi.resize(NG, 0.0);
    E.resize(NG, 0.0);
}

void Fields::deposit_charge(const std::vector<double>& x, double alpha_p) {
    std::fill(rho.begin(), rho.end(), 0.0);

    for (double xp : x) {
        int g = static_cast<int>(xp / dx) % NG;
        rho[g] += -alpha_p / dx;  // electrones negativos
    }
}

void Fields::solve_poisson() {
    // simple solver (no FFT): phi[g] = -rho[g]*dx^2 / 2 (aprox)
    // -> aquí puedes luego meter un solver más realista
    for (int g = 0; g < NG; g++) {
        phi[g] = -0.5 * rho[g] * dx * dx;
    }
}

void Fields::compute_electric_field() {
    for (int g = 0; g < NG; g++) {
        int g_left = (g - 1 + NG) % NG;
        int g_right = (g + 1) % NG;
        E[g] = (phi[g_left] - phi[g_right]) / (2.0 * dx);
    }
}

