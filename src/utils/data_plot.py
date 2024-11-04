from typing import Tuple, Dict
from functools import partial
import matplotlib.pyplot as plt
import pandas as pd
import os

def load_data(filepath: str) -> pd.DataFrame:
    return pd.read_csv(filepath, sep=r"\s+", engine='python')

def get_style_config() -> Dict:
    return {
        'figure.figsize': [15, 5],
        'font.size': 10,
        'axes.labelsize': 10,
        'axes.titlesize': 11,
        'xtick.labelsize': 9,
        'ytick.labelsize': 9,
        'legend.fontsize': 9,
        'figure.titlesize': 11
    }

def get_line_style() -> Dict:
    return {
        'markersize': 4,
        'linewidth': 1,
        'markeredgewidth': 1
    }

def create_plot() -> Tuple[plt.Figure, Tuple[plt.Axes, plt.Axes]]:
    return plt.subplots(1, 2, figsize=(15, 5))

def plot_algorithm_comparison(ax: plt.Axes, data: pd.DataFrame, x_col: str, 
                            y_cols: Tuple[str, str], title: str) -> None:
    line_style = get_line_style()
    ax.plot(data[x_col], data[y_cols[0]], label='Dynamic Programming',
            marker='o', color='magenta', **line_style)
    ax.plot(data[x_col], data[y_cols[1]], label='Greedy',
            marker='x', color='cyan', **line_style)
    ax.set_xlabel('n')
    ax.set_ylabel(title)
    ax.tick_params(axis='x', rotation=45)
    ax.grid(True, linestyle=':', alpha=0.7)
    ax.legend()

def configure_plot_labels(fig: plt.Figure, ax1: plt.Axes, ax2: plt.Axes) -> None:
    ax1.text(-0.1, -0.15, '(a)', transform=ax1.transAxes, fontsize=10)
    ax2.text(-0.1, -0.15, '(b)', transform=ax2.transAxes, fontsize=10)
    fig.suptitle('Dynamic Programming vs. Greedy', fontsize=11, y=0.98)
    fig.text(0.25, 0.02, 'Valor total de venda.', ha='center', fontsize=10)
    fig.text(0.75, 0.02, 'Tempo de execução dos algoritmos.', ha='center', fontsize=10)

def save_plot(fig: plt.Figure, filename: str) -> None:
    script_dir = os.path.dirname(os.path.abspath(__file__))
    results_dir = os.path.join(script_dir, '..', 'results')
    os.makedirs(results_dir, exist_ok=True)
    filepath = os.path.join(results_dir, filename)
    fig.savefig(filepath, dpi=300, bbox_inches='tight',
                facecolor='white', edgecolor='none')

def create_visualization(data: pd.DataFrame) -> None:
    plt.style.use('seaborn-v0_8-whitegrid')
    plt.rcParams.update(get_style_config())
    
    fig, (ax1, ax2) = create_plot()
    
    plot_algorithm_comparison(ax1, data, 'n', ('vDP', 'vGreedy'), 'Valor total de venda')
    plot_algorithm_comparison(ax2, data, 'n', ('tDP', 'tGreedy'), 'Tempo de execução')
    
    configure_plot_labels(fig, ax1, ax2)
    plt.subplots_adjust(bottom=0.2, wspace=0.3)
    
    save_plot(fig, "comparacao_dp_vs_greedy.png")
    plt.show()

def main() -> None:
    file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "data", "resultados.txt")
    
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Arquivo '{file_path}' não encontrado no diretório do script.")
    
    data = load_data(file_path)
    create_visualization(data)

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Erro: {str(e)}")
        exit(1)