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
    std::fill(rho.begin(), rho.end(), 1.0); // Background charge

    for (double xp : x) {
        double g = xp / dx;
        int g0 = static_cast<int>(g) % NG;
        double frac = g - g0;
        int g1 = (g0 + 1) % NG;

        rho[g0] += -alpha_p * (1 - frac) / dx;
        rho[g1] += -alpha_p * frac / dx;
    }
}

void Fields::solve_poisson() {
    // Implement a proper tridiagonal solver
    int n = NG;
    std::vector<double> a(n-1, 1.0);
    std::vector<double> b(n, -2.0);
    std::vector<double> c(n-1, 1.0);
    std::vector<double> d(n);
    
    for (int i = 0; i < n; i++) {
        d[i] = rho[i] * dx * dx;
    }
    
    // Thomas algorithm
    for (int i = 1; i < n; i++) {
        double m = a[i-1] / b[i-1];
        b[i] -= m * c[i-1];
        d[i] -= m * d[i-1];
    }
    
    phi[n-1] = d[n-1] / b[n-1];
    for (int i = n-2; i >= 0; i--) {
        phi[i] = (d[i] - c[i] * phi[i+1]) / b[i];
    }
}

void Fields::compute_electric_field() {
    // More accurate electric field calculation
    for (int g = 0; g < NG; g++) {
        int g_prev = (g == 0) ? NG-1 : g-1;
        int g_next = (g == NG-1) ? 0 : g+1;
        E[g] = (phi[g_prev] - phi[g_next]) / (2.0 * dx);
    }
}

