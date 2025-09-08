import numpy as np
import matplotlib.pyplot as plt

# Cargar datos del CSV
data = np.genfromtxt("diagnostics.csv", delimiter=',', skip_header=1)

time = data[:, 0]
momentum = data[:, 1]
Ekin = data[:, 2]
Epot = data[:, 3]
Etotal = data[:, 4]

# Configuración de estilo para gráficas más claras
plt.rcParams['figure.figsize'] = [10, 6]
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['axes.grid'] = True
plt.rcParams['grid.alpha'] = 0.3
plt.rcParams['font.size'] = 12

# Figura 1: Todas las curvas juntas
plt.figure(1)
plt.plot(time, momentum, label='Momentum', color='purple')
plt.plot(time, Ekin, label='Kinetic Energy', color='blue')
plt.plot(time, Epot, label='Potential Energy', color='red')
plt.plot(time, Etotal, label='Total Energy', color='green', linestyle='--')

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Two-Stream Instability PIC 1D - All Quantities")
plt.legend()
plt.tight_layout()

# Figura 2: Las cuatro gráficas separadas
plt.figure(2, figsize=(12, 8))

# Subplot 1: Momentum
plt.subplot(2, 2, 1)
plt.plot(time, momentum, color='purple')
plt.xlabel('Time')
plt.ylabel('Momentum')
plt.title('Momentum Evolution')
plt.grid(True, alpha=0.3)

# Subplot 2: Kinetic Energy
plt.subplot(2, 2, 2)
plt.plot(time, Ekin, color='blue')
plt.xlabel('Time')
plt.ylabel('Kinetic Energy')
plt.title('Kinetic Energy Evolution')
plt.grid(True, alpha=0.3)

# Subplot 3: Potential Energy
plt.subplot(2, 2, 3)
plt.plot(time, Epot, color='red')
plt.xlabel('Time')
plt.ylabel('Potential Energy')
plt.title('Potential Energy Evolution')
plt.grid(True, alpha=0.3)

# Subplot 4: Total Energy
plt.subplot(2, 2, 4)
plt.plot(time, Etotal, color='green')
plt.xlabel('Time')
plt.ylabel('Total Energy')
plt.title('Total Energy Evolution')
plt.grid(True, alpha=0.3)

plt.tight_layout()

# Mostrar ambas figuras
plt.show()
