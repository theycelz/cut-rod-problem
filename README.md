# Problema do Corte da Tora

Este projeto implementa o problema do corte da tora de madeira utilizando dois algoritmos: um baseado em programação dinâmica e outro utilizando uma estratégia gulosa (greedy). O objetivo é determinar o valor máximo de venda que pode ser obtido ao cortar uma tora de comprimento `n` metros em pedaços menores.

## Descrição

Uma empresa compra longas toras de madeira e as corta em pedaços menores para revenda. Os cortes são realizados de tal modo que os pedaços resultantes têm sempre comprimento inteiro. Para cada `i=1,2,...,n`, a empresa cobra o preço `p_i` por uma tora de comprimento `i`.

### Algoritmos Implementados

1. **Programação Dinâmica (Dynamic Programming - DP)**:
   - Implementado na função `cut_rod_dp`.
   - Utiliza uma abordagem bottom-up para calcular o valor máximo de venda.

2. **Estratégia Gulosa (Greedy)**:
   - Implementado na função `cut_rod_greedy`.
   - Utiliza a densidade (valor por metro) para decidir os cortes.

## Parâmetros de Execução

- `inc`: Tamanho inicial da entrada.
- `fim`: Tamanho final da entrada.
- `stp`: Intervalo entre dois tamanhos de entrada.

## Entrada e Saída

O programa gera conjuntos de dados de entrada pseudoaleatórios e executa os algoritmos propostos, mostrando o valor total de venda obtido por cada um e registrando seus tempos de execução. Ao final, mostra a porcentagem de acerto da solução gulosa em relação à solução da programação dinâmica.

### Exemplo de Entrada e Saída

Para casos de teste com `n=1000, 2000, ..., 20000`, o programa exibe uma tabela com os seguintes campos:

- `n`: Comprimento da tora.
- `vDP`: Valor máximo de venda usando programação dinâmica.
- `tDP (s)`: Tempo de execução do algoritmo de programação dinâmica.
- `vGreedy`: Valor máximo de venda usando a estratégia gulosa.
- `tGreedy (s)`: Tempo de execução do algoritmo guloso.
- `%`: Porcentagem de acerto da solução gulosa em relação à solução da programação dinâmica.

## Gráficos

O programa gera e salva dois gráficos:

1. **Valor Total de Venda** (`valor_total_venda.png`):
   - Compara os valores de venda obtidos pelos dois algoritmos.

2. **Tempo de Execução** (`tempo_execucao.png`):
   - Compara os tempos de execução dos dois algoritmos.

## Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/cut-rod-problem.git
   cd cut-rod-problem
   ```
2. Instale as dependências:
   ```bash
   pip install -r requirements.txt
   ```
3. Execute o script:
      ```bash
    python automate.py
   ```
