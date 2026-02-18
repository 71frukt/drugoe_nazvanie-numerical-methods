import numpy as np
import matplotlib.pyplot as plt

def generate_wiener_process():
    T       = 1.0
    dt      = 0.0001
    n_paths = 1000
    
    n_steps = int(T / dt)
    
    timeline = np.linspace(0, T, n_steps + 1)
    
    xi = np.random.normal(loc=0.0, scale=1.0, size=(n_paths, n_steps))
    
    increments = np.sqrt(dt) * xi
    
    cumulative_sum = np.cumsum(increments, axis=1)
    
    zeros = np.zeros((n_paths, 1))
    paths = np.hstack((zeros, cumulative_sum))
    
    # --- Отрисовка ---
    plt.figure(figsize=(12, 7))
    
    # Рисуем все траектории
    # .T (транспонирование) нужно, так как plot рисует столбцы как отдельные линии
    # alpha=0.1 делает линии полупрозрачными, чтобы было видно плотность распределения
    plt.plot(timeline, paths.T, color='darkcyan', alpha=0.05, linewidth=0.5)
    
    # Дополнительно: Нарисуем границы 3 сигм (3 корня из t), чтобы проверить теорию
    # Для Винеровского процесса ст. отклонение в момент t равно sqrt(t)
    sigma_bound = 3 * np.sqrt(timeline)
    plt.plot(timeline,  sigma_bound, color='red',   linestyle='--', linewidth=2, label='Граница $\pm 3\sqrt{t}$')
    plt.plot(timeline, -sigma_bound, color='red',   linestyle='--', linewidth=2)
    
    sigma_bound = 2 * np.sqrt(timeline)
    plt.plot(timeline,  sigma_bound, color='green', linestyle='--', linewidth=2, label='Граница $\pm 2\sqrt{t}$')
    plt.plot(timeline, -sigma_bound, color='green', linestyle='--', linewidth=2)

    plt.title(f'Винеровский процесс: {n_paths} траекторий\n$T={T}, \delta={dt}$', fontsize=14)
    plt.xlabel('Время (t, сек)', fontsize=12)
    plt.ylabel('Значение процесса ($B_t$)', fontsize=12)
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.legend(loc='upper left')
    
    # Показать график
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    generate_wiener_process()