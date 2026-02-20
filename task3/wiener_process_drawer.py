import numpy as np
import matplotlib.pyplot as plt

def generate_wiener_process():
    T       = 1.0
    dt      = 0.0001
    n_paths = 5000
    
    n_steps = int(T / dt)
    
    timeline = np.linspace(0, T, n_steps + 1)
    
    xi = np.random.normal(loc=0.0, scale=1.0, size=(n_paths, n_steps))
    
    increments = np.sqrt(dt) * xi
    
    cumulative_sum = np.cumsum(increments, axis=1)
    
    zeros = np.zeros((n_paths, 1))
    paths = np.hstack((zeros, cumulative_sum))
    
    # Вычисление статистики для второго графика
    sigma_bound = 3 * np.sqrt(timeline)
    
    outside_condition = np.abs(paths[:, 1:]) > sigma_bound[1:]
    outside_counts = np.sum(outside_condition, axis=0)
    outside_percentage = (outside_counts / n_paths) * 100
    
    # Вычисление кумулятивного среднего для процента выходов
    cumulative_avg_percentage = np.cumsum(outside_percentage) / np.arange(1, len(outside_percentage) + 1)
    
    # ----------------------------------- Отрисовка -------------------------------------------------------------
    fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1, figsize=(12, 12))
    
    # график 1 - траектории Винеровского процесса ---
    ax1.plot(timeline, paths.T, color='darkcyan', alpha=0.05, linewidth=0.5)
    
    ax1.plot(timeline,  sigma_bound, color='red', linestyle='--', linewidth=2, label='Граница $\pm 3\sqrt{t}$')
    ax1.plot(timeline, -sigma_bound, color='red', linestyle='--', linewidth=2)

    ax1.set_title(f'Винеровский процесс: {n_paths} траекторий\n$T={T}, \delta={dt}$', fontsize=14)
    ax1.set_xlabel('Время (t, сек)', fontsize=12)
    ax1.set_ylabel('Значение процесса ($B_t$)', fontsize=12)
    ax1.grid(True, which='both', linestyle='--', alpha=0.7)
    ax1.legend(loc='upper left')
    
    # график 2 - процент траекторий вне границ 3 сигм ---
    ax2.plot(timeline[1:], outside_percentage, color='blue', alpha=0.3, label='Эмпирический процент')
    
    ax2.plot(timeline[1:], cumulative_avg_percentage, color='darkorange', linewidth=2, label='Среднее значение до точки x')
    
    ax2.axhline(y=0.27, color='red', linestyle='--', linewidth=2, label='Теоретический предел (0.27%)')
    
    ax2.set_title('Процент траекторий, вышедших за границы $\pm 3\sigma$', fontsize=14)
    ax2.set_xlabel('Время (t, сек)', fontsize=12)
    ax2.set_ylabel('Доля вышедших траекторий (%)', fontsize=12)
    
    ax2.set_xlim(0, T)
    ax2.set_ylim(0, 0.8)
    
    ax2.grid(True, linestyle='--', alpha=0.7)
    ax2.legend(loc='upper right')
    
    plt.tight_layout()
    plt.show()

# ----------------------------------- main ----------------------------------------------------------------------
if __name__ == "__main__":
    generate_wiener_process()