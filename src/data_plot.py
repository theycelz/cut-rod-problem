import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def carregar_dados(arquivo):
    return pd.read_csv(arquivo, sep="\s+", engine='python')  
def plotar_graficos(dados):
    plt.figure(figsize=(14, 6))

    # Gráfico de Valores: DP vs Greedy
    plt.subplot(1, 2, 1)
    plt.plot(dados['n'], dados['vDP'], label="DP", color="blue", marker="o")
    plt.plot(dados['n'], dados['vGreedy'], label="Greedy", color="green", marker="s")
    plt.xlabel("Tamanho da Entrada (n)")
    plt.ylabel("Valor Total")
    plt.title("Comparação de Valores: DP vs Greedy")
    plt.legend()
    plt.grid(True, which="both", linestyle="--", linewidth=0.5, color="gray")

    # Gráfico de Tempos com Escala Logarítmica
    plt.subplot(1, 2, 2)
    plt.plot(dados['n'], dados['tDP'], label="Tempo DP", color="red", marker="^")
    plt.plot(dados['n'], dados['tGreedy'], label="Tempo Greedy", color="purple", marker="x")
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Tamanho da Entrada (n)")
    plt.ylabel("Tempo (s)")
    plt.title("Comparação de Tempo: DP vs Greedy")
    plt.legend()
    plt.grid(True, which="both", linestyle="--", linewidth=0.5, color="gray")

    # Salva o gráfico em alta resolução
    plt.tight_layout()
    plt.savefig("comparacao_dp_vs_greedy.png", dpi=300)
    plt.show()
