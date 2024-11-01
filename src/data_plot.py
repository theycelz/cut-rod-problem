import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

def carregar_dados(arquivo):
    return pd.read_csv(arquivo, sep=r"\s+", engine='python')

def configurar_estilo():
    # Configuração para estilo mais acadêmico
    plt.style.use('seaborn-v0_8-whitegrid')
    plt.rcParams['figure.figsize'] = [12, 5]  # Formato mais largo que alto
    plt.rcParams['font.size'] = 10
    plt.rcParams['axes.labelsize'] = 10
    plt.rcParams['axes.titlesize'] = 11
    plt.rcParams['xtick.labelsize'] = 9
    plt.rcParams['ytick.labelsize'] = 9
    plt.rcParams['legend.fontsize'] = 9
    plt.rcParams['figure.titlesize'] = 11

def plotar_graficos(dados):
    configurar_estilo()
    
    # Criar figura com dois subplots lado a lado
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    
    # Configurações de estilo comuns
    linha_estilo = {
        'markersize': 4,
        'linewidth': 1,
        'markeredgewidth': 1,
    }
    
    # Gráfico de Valores
    ax1.plot(dados['n'], dados['vDP'], 
             label='Dynamic Programming',
             marker='o',
             color='magenta',
             **linha_estilo)
    ax1.plot(dados['n'], dados['vGreedy'],
             label='Greedy',
             marker='x',
             color='cyan',
             **linha_estilo)
    
    # Gráfico de Tempo
    ax2.plot(dados['n'], dados['tDP'],
             label='Dynamic Programming',
             marker='o',
             color='magenta',
             **linha_estilo)
    ax2.plot(dados['n'], dados['tGreedy'],
             label='Greedy',
             marker='x',
             color='cyan',
             **linha_estilo)
    
    # Configuração dos títulos
    fig.suptitle('Dynamic Programming vs. Greedy', fontsize=11, y=0.98)
    
    # Configuração do primeiro gráfico
    ax1.set_xlabel('n')
    ax1.set_ylabel('Valor total de venda')
    ax1.grid(True, linestyle=':', alpha=0.7)
    ax1.legend()
    
    # Configuração do segundo gráfico
    ax2.set_xlabel('n')
    ax2.set_ylabel('Tempo de execução')
    ax2.grid(True, linestyle=':', alpha=0.7)
    ax2.legend()
    
    # Adicionar rótulos (a) e (b)
    ax1.text(-0.1, -0.15, '(a)', transform=ax1.transAxes, fontsize=10)
    ax2.text(-0.1, -0.15, '(b)', transform=ax2.transAxes, fontsize=10)
    
    # Ajustar layout
    plt.tight_layout()
    
    # Adicionar subtítulos abaixo dos gráficos
    fig.text(0.25, 0.02, 'Valor total de venda.', ha='center', fontsize=10)
    fig.text(0.75, 0.02, 'Tempo de execução dos algoritmos.', ha='center', fontsize=10)
    
    # Salvar com maior resolução
    plt.savefig("comparacao_dp_vs_greedy.png", 
                dpi=300,
                bbox_inches='tight',
                facecolor='white',
                edgecolor='none')
    
    plt.show()

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    arquivo_dados = os.path.join(script_dir, "resultados.txt")
    
    if not os.path.exists(arquivo_dados):
        print(f"Erro: O arquivo '{arquivo_dados}' não foi encontrado.")
        print("Por favor, certifique-se de que o arquivo existe no mesmo diretório do script.")
        exit(1)
        
    try:
        dados = carregar_dados(arquivo_dados)
        plotar_graficos(dados)
    except Exception as e:
        print(f"Erro ao processar os dados: {str(e)}")
        exit(1)