#include "diagnostics.hh"
#include <cmath>

double diagnostics::momentum(const std::vector<double>& v, double alpha_p) {
    double sum = 0.0;
    for (auto vi : v) sum += vi;
    return sum * alpha_p;
}

double diagnostics::kinetic_energy(const std::vector<double>& v, double alpha_p) {
    double sum = 0.0;
    for (auto vi : v) sum += 0.5 * vi * vi;
    return sum * alpha_p;
}

double diagnostics::potential_energy(const std::vector<double>& E, double dx) {
    double sum = 0.0;
    for (auto Ei : E) sum += 0.5 * Ei * Ei * dx;
    return sum;
}

