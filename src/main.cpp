#include "particles.hh"
#include "fields.hh"
#include "diagnostics.hh"
#include <iostream>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


int main() {
    // parámetros
    int N = 1000 * 2;
    int NG = 32 * 2;
    double L = M_PI;
    double dt = 0.5 / 2;
    int NT = 200 * 2;
    double V0 = 0.2;
    double VT = 0;
    double perturb = 1.0;
    double alpha_p = (1.0 * L) / N;

    Particles particles(N, L);
    particles.initialize_two_stream(V0, perturb, VT);

    // Abrir archivo CSV
    std::ofstream fout("diagnostics.csv");
    std::ofstream phase_out("phase_space.csv");
    fout << "time,momentum,Ekin,Epot,Etotal\n";
    phase_out << "time,particle_id,x,v,beam_id\n";

    Fields fields(NG, L);

    for (int it = 0; it < NT; it++) {
        fields.deposit_charge(particles.x, alpha_p);
        fields.solve_poisson();
        fields.compute_electric_field();

        particles.push(dt, fields.E, fields.dx);

        double mom = diagnostics::momentum(particles.v, alpha_p);
        double Ek  = diagnostics::kinetic_energy(particles.v, alpha_p);
        double Ep  = diagnostics::potential_energy(fields.E, fields.dx);

        fout << it*dt << ","
                  << mom << ","
                  << Ek << ","
                  << Ep << ","
                  << Ek+Ep << "\n";

        // Guardar datos del espacio de fase cada 10 de tiempo
        if (it % 1 == 0) {
            for (int i = 0; i < N; i++) {
                phase_out << it*dt << "," << i << "," << particles.x[i] << ","
                        << particles.v[i] << "," << particles.beam_id[i] << "\n";
            }
        }
    }
    
    std::cout << "Simulation completed.\n";
    fout.close();
    std::cout << "CSV generated: diagnostics.csv\n";
    phase_out.close();
    std::cout << "CSV generated: phase_space.csv\n";
    return 0;
}

