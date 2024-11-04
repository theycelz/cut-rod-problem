# README - Problema do Corte da Tora

## Descrição
Implementação de dois algoritmos para resolver o problema do corte da tora de madeira:
- Solução por Programação Dinâmica (bottom-up)
- Solução por Algoritmo Guloso (baseado em densidade)

## Requisitos
- GCC (GNU Compiler Collection)
- Python 3.x
- Bibliotecas Python: `pandas`, `matplotlib`

## Compilação
Para compilar o programa, execute no terminal:
```bash
make
```

## Execução
Após compilar, execute:
```bash
./rod_cutting
```

## Análise de Resultados
Para analisar os resultados gerados pelo programa em `resultados.txt`, execute:
```bash
python analysis_stats.py
```

## Visualização de Dados
Para gerar visualizações dos dados, execute:
```bash
python data_plot.py
```

## Arquivos Gerados
O programa gera automaticamente:
- `resultados.txt`: Tabela com os resultados formatados (n, Valor DP, Tempo DP, Valor Greedy, Tempo Greedy, Precisão)

## Estrutura do Código
- `main.c`: Programa principal com entrada de dados
- `rod_cutting.c`: Implementação dos algoritmos e funções auxiliares
- `rod_cutting.h`: Definições de estruturas e protótipos
- `analysis_stast.py`: Análise estatística dos resultados
- `data_plot.py`: Geração de gráficos comparativos dos resultados

## Limpeza
Para remover os arquivos compilados:
```bash
make clean
```

## Observações
- Os preços são gerados automaticamente seguindo uma ordem não decrescente