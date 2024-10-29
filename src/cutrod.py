"""
Implementação do Problema do Corte da Tora
Autores: Eos Xavier e Livia Rosa Duarte Ripardo
"""
import numpy as np
import matplotlib.pyplot as plt
import time
import random
from tabulate import tabulate


def gera_precos(n):
    precos = [random.randint(1, n) for _ in range(n)]
    precos.sort()
    return precos


def cut_rod_dp(precos, n):
    val = [0] * (n + 1)
    for i in range(1, n + 1):
        max_val = float('-inf')
        for j in range(i):
            max_val = max(max_val, precos[j] + val[i - j - 1])
        val[i] = max_val
    return val[n]


def cut_rod_greedy(precos, n):
    densidades = [(precos[i] / (i + 1), i + 1, precos[i]) for i in range(n)]
    densidades.sort(reverse=True)
    total_valor = 0
    comprimento_restante = n
    while comprimento_restante > 0:
        for densidade, comprimento, preco in densidades:
            if comprimento <= comprimento_restante:
                qtd = comprimento_restante // comprimento
                total_valor += preco * qtd
                comprimento_restante -= comprimento * qtd
                break
        else:
            break
    return total_valor


inc = 1000
fim = 20000
stp = 1000

resultados = []

for n in range(inc, fim + 1, stp):
    precos = gera_precos(n)

    inicio_dp = time.time()
    v_dp = cut_rod_dp(precos, n)
    fim_dp = time.time()
    t_dp = fim_dp - inicio_dp

    inicio_greedy = time.time()
    v_greedy = cut_rod_greedy(precos, n)
    fim_greedy = time.time()
    t_greedy = fim_greedy - inicio_greedy

    porcentagem = (v_greedy / v_dp) * 100 if v_dp != 0 else 0
    resultados.append([n, v_dp, t_dp, v_greedy, t_greedy, porcentagem])

# Exibir a tabela de resultados e salvar em um arquivo
cabecalho = ["n", "vDP", "tDP (s)", "vGreedy", "tGreedy (s)", "%"]
output_text = tabulate(resultados, headers=cabecalho, floatfmt=".6f")
print(output_text)

with open("output.txt", "w") as f:
    f.write(output_text)

# Preparar dados para os gráficos
ns = [row[0] for row in resultados]
v_dps = [row[1] for row in resultados]
v_greedys = [row[3] for row in resultados]
t_dps = [row[2] for row in resultados]
t_greedys = [row[4] for row in resultados]

# Gráfico de Valor Total de Venda
plt.figure(figsize=(10, 6))
plt.plot(ns, v_dps, marker='o', linestyle='-', color='blue', label='DP')
plt.plot(ns, v_greedys, marker='s', linestyle='-', color='red', label='Greedy')
plt.title("Dynamic Programming vs. Greedy\nValor total de venda")
plt.xlabel("n")
plt.ylabel("Valor total de venda")
plt.legend()
plt.grid(True)
plt.savefig("valor_total_venda.png")
plt.close()

# Gráfico de Tempo de Execução
plt.figure(figsize=(10, 6))
plt.plot(ns, t_dps, marker='o', linestyle='-', color='blue', label='DP')
plt.plot(ns, t_greedys, marker='s', linestyle='-', color='red', label='Greedy')
plt.title("Dynamic Programming vs. Greedy\nTempo de execução dos algoritmos")
plt.xlabel("n")
plt.ylabel("Tempo de execução (segundos)")
plt.legend()
plt.grid(True)
plt.savefig("tempo_execucao.png")
plt.close()
