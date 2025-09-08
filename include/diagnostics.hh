#ifndef DIAGNOSTICS_HH
#define DIAGNOSTICS_HH

#include <vector>

namespace diagnostics {
    double momentum(const std::vector<double>& v, double alpha_p);
    double kinetic_energy(const std::vector<double>& v, double alpha_p);
    double potential_energy(const std::vector<double>& E, double dx);
}

#endif

