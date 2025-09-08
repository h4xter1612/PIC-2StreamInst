import numpy as np
import matplotlib.pyplot as plt

# Cargar CSV
data = np.genfromtxt("diagnostics.csv", delimiter=',', skip_header=1)

time = data[:, 0]
momentum = data[:, 1]
Ekin = data[:, 2]
Epot = data[:, 3]
Etotal = data[:, 4]

# Graficar
plt.figure(figsize=(10,6))
plt.plot(time, momentum, label='Momentum')
plt.plot(time, Ekin, label='Kinetic Energy')
plt.plot(time, Epot, label='Potential Energy')
plt.plot(time, Etotal, label='Total Energy')

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Two-Stream Instability PIC 1D")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

