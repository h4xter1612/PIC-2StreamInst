#ifndef FIELDS_HH
#define FIELDS_HH

#include <vector>

struct Fields {
    int NG;          // número de puntos en la malla
    double L;        // longitud del dominio
    double dx;       // tamaño de celda
    std::vector<double> rho; // densidad de carga
    std::vector<double> phi; // potencial
    std::vector<double> E;   // campo eléctrico

    Fields(int NG_, double L_);

    void deposit_charge(const std::vector<double>& x, double alpha_p);
    void solve_poisson();
    void compute_electric_field();
};

#endif

