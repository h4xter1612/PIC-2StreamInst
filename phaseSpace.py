import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import colors

# Cargar datos del espacio de fase
phase_data = np.genfromtxt("phase_space.csv", delimiter=',', skip_header=1)

# Extraer columnas
time_steps = phase_data[:, 0]
particle_ids = phase_data[:, 1]
x_positions = phase_data[:, 2]
v_velocities = phase_data[:, 3]
beam_ids = phase_data[:, 4]

# Obtener tiempos únicos
unique_times = np.unique(time_steps)

# Configurar la figura
plt.rcParams['figure.figsize'] = [10, 6]
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['font.size'] = 12

# Tamaño de los puntos
point_size = 8

# Figura 1: Evolución del espacio de fase en el tiempo
fig1, ax1 = plt.subplots()
scatter = ax1.scatter([], [], s=point_size, c=[], cmap='coolwarm', vmin=-1, vmax=1, alpha=0.6)
time_text = ax1.text(0.02, 0.95, '', transform=ax1.transAxes, fontsize=12)  # Texto para mostrar el tiempo
ax1.set_xlim(0, np.pi)
ax1.set_ylim(-0.8, 0.8)
ax1.set_xlabel('Position (x)')
ax1.set_ylabel('Velocity (v)')
ax1.set_title('Two-Beam Instability - Phase space time evolution')

# Función de animación
def update(frame):
    time = unique_times[frame]
    mask = time_steps == time
    x = x_positions[mask]
    v = v_velocities[mask]
    b = beam_ids[mask]
    
    scatter.set_offsets(np.c_[x, v])
    scatter.set_sizes(np.full(len(x), point_size))
    scatter.set_array(b)
    time_text.set_text(f'Time: {time:.2f}')  # Actualizar el texto del tiempo
    
    return scatter, time_text  # Devolver ambos objetos para la animación

# Crear animación
ani = animation.FuncAnimation(fig1, update, frames=len(unique_times), 
                              interval=50, blit=True)

# Guardar la animación como MP4 (más eficiente)
# try:
#     # Intentar guardar como MP4 (requiere ffmpeg)
#     ani.save('phase_space_evolution.mp4', writer='ffmpeg', fps=20, 
#              bitrate=1000, dpi=150)
#     print("Animación guardada como phase_space_evolution.mp4")
# except:
#     # Si falla, guardar como GIF (más compatible pero más pesado)
#     try:
#         ani.save('phase_space_evolution.gif', writer='pillow', fps=10)
#         print("Animación guardada como phase_space_evolution.gif")
#     except:
#         print("No se pudo guardar la animación. Asegúrate de tener ffmpeg o pillow instalado.")

# Figura 2: Espacio de fase en tiempos seleccionados
fig2, axs = plt.subplots(2, 2, figsize=(12, 10))
selected_times = [unique_times[0], unique_times[len(unique_times)//3], 
                 unique_times[2*len(unique_times)//3], unique_times[-1]]

for i, time in enumerate(selected_times):
    ax = axs[i//2, i%2]
    mask = time_steps == time
    x = x_positions[mask]
    v = v_velocities[mask]
    b = beam_ids[mask]
    
    # Separar por haces
    mask_beam1 = b == 1
    mask_beam2 = b == -1
    
    # Aplicar el tamaño de punto especificado
    ax.scatter(x[mask_beam1], v[mask_beam1], s=point_size, color='red', alpha=0.6, label='Beam 1 (v > 0)')
    ax.scatter(x[mask_beam2], v[mask_beam2], s=point_size, color='blue', alpha=0.6, label='Beam 2 (v < 0)')
    
    ax.set_xlim(0, np.pi)
    ax.set_ylim(-0.8, 0.8)
    ax.set_xlabel('Position (x)')
    ax.set_ylabel('Velocity (v)')
    ax.set_title(f'Time = {time:.2f}')
    ax.legend()
    ax.grid(True, alpha=0.3)

plt.tight_layout()

# Mostrar las figuras
plt.show()

