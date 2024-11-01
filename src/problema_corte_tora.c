/**
 * problema_corte_tora.c
 * 
 * Implementação dos algoritmos de Programação Dinâmica e Guloso
 * para resolver o problema do corte de tora, comparando suas
 * performances e resultados.
 * 
 * Autores:
 * - Livia
 * - Eos
 * 
 * Data: Abril/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define INC 1000  // Valor inicial
#define FIM 20000 // Valor final 
#define STP 1000  // Incremento

/**
 * Gera preços aleatórios para uma tora de tamanho n.
 * 
 * @param n Tamanho da tora
 * @return Array com os preços gerados ou NULL em caso de erro
 */
int* gera_precos(int n) {
    if (n <= 0) {
        printf("Erro: tamanho da tora deve ser positivo\n");
        return NULL;
    }

    int* precos = (int*)malloc(n * sizeof(int));
    if (!precos) {
        printf("Erro: falha na alocação de memória\n");
        return NULL;
    }

    precos[0] = 1 + (rand() % 3);
    int num_jumps = 3 + (rand() % 3);  
    int jump_positions[5];  
    
    for (int i = 0; i < num_jumps; i++) {
        jump_positions[i] = (n / (num_jumps + 1)) * (i + 1) + (rand() % (n / (num_jumps + 1)));
    }

    for (int i = 1; i < n; i++) {
        bool is_jump = false;
        for (int j = 0; j < num_jumps; j++) {
            if (i == jump_positions[j]) {
                is_jump = true;
                break;
            }
        }

        if (is_jump) {
            int max_jump = (n - precos[i-1]) / 2;
            int jump = max_jump / 2 + (rand() % (max_jump / 2));
            precos[i] = precos[i-1] + jump;
        } else {
            int base_increment = 1 + (rand() % 3);
            double position_factor = (double)i / n;
            int extra_increment = (int)(position_factor * 5);
            
            precos[i] = precos[i-1] + base_increment + extra_increment;
        }

        if (precos[i] > n) {
            precos[i] = n;
        }

        if (precos[i] <= precos[i-1]) {
            precos[i] = precos[i-1] + 1;
        }
    }

    // Cria alguns "vales" de preço-densidade para desafiar o algoritmo guloso
    for (int i = n/4; i < n; i += n/4) {
        int valley_size = 3 + (rand() % 5);  
        for (int j = 0; j < valley_size && (i+j) < n; j++) {
            double current_density = (double)precos[i+j] / (i+j+1);
            double target_density = current_density * 0.7;  
            int new_price = (int)(target_density * (i+j+1));
            
            if (new_price > precos[i+j-1] && new_price <= n) {
                precos[i+j] = new_price;
            }
        }
    }

    return precos;
}

// Função auxiliar para imprimir os preços (para debug)
void imprime_precos(int* precos, int n) {
    printf("Preços gerados:\n");
    for (int i = 0; i < n; i++) {
        printf("p[%d] = %d\n", i+1, precos[i]);
    }
}

/**
 * Resolve o problema do corte de tora usando programação dinâmica bottom-up.
 * 
 * @param precos Array com os preços para cada tamanho
 * @param n Tamanho da tora
 * @return Valor máximo que pode ser obtido
 */
int cut_rod_dp(int* precos, int n) {
    if (!precos || n < 0) {
        return -1; 
    }

    int* rod = (int*)malloc((n + 1) * sizeof(int));
    if (!rod) {
        return -1;  
    }

    rod[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = precos[i-1];  
        
        for (int j = 1; j < i; j++) {
            int val = precos[j-1] + rod[i-j];
            if (val > max_val) {
                max_val = val;
            }
        }
        rod[i] = max_val;
    }
    int resultado = rod[n];
    free(rod);

    return resultado;
}

// Função auxiliar para testes
void testa_dp() {
    int precos_teste[] = {1, 5, 8, 9, 10};
    int n_teste = 5;
    int resultado = cut_rod_dp(precos_teste, n_teste);
    printf("Teste DP n=5: %d (esperado: 13)\n", resultado);
    printf("Teste null: %d (esperado: -1)\n", cut_rod_dp(NULL, 5));
    printf("Teste n negativo: %d (esperado: -1)\n", cut_rod_dp(precos_teste, -1));
}

/**
 * Estrutura para armazenar densidade e índice original
 */
typedef struct {
    double densidade;
    int indice;
} DensidadeInfo;

/**
 * Função de comparação para ordenação decrescente por densidade
 */
static int compara_densidade(const void* a, const void* b) {
    DensidadeInfo* d1 = (DensidadeInfo*)a;
    DensidadeInfo* d2 = (DensidadeInfo*)b;
    if (d1->densidade < d2->densidade) return 1;
    if (d1->densidade > d2->densidade) return -1;
    return 0;
}

/**
 * Resolve o problema do corte de tora usando algoritmo guloso.
 * 
 * @param precos Array com os preços para cada tamanho
 * @param n Tamanho da tora
 * @return Valor obtido pela estratégia gulosa
 */
int cut_rod_greedy(int* precos, int n) {
    if (!precos || n <= 0) {
        return -1;
    }

    DensidadeInfo* densidades = (DensidadeInfo*)malloc(n * sizeof(DensidadeInfo));
    if (!densidades) return -1;

    for (int i = 0; i < n; i++) {
        densidades[i].densidade = (double)precos[i] / (i + 1);
        densidades[i].indice = i;
    }

    qsort(densidades, n, sizeof(DensidadeInfo), compara_densidade);
    int valor_total = 0;
    int comprimento_restante = n;

    while (comprimento_restante > 0) {
        bool cortou = false;
        
        for (int i = 0; i < n && !cortou; i++) {
            int comp_corte = densidades[i].indice + 1;
            if (comp_corte <= comprimento_restante) {
                valor_total += precos[densidades[i].indice];
                comprimento_restante -= comp_corte;
                cortou = true;
            }
        }
        
        if (!cortou) break;
    }

    free(densidades);
    return valor_total;
}

// Função auxiliar para testes
void testa_greedy() {
    int precos_teste[] = {1, 5, 8, 9, 10};
    int n_teste = 5;
    
    int resultado_greedy = cut_rod_greedy(precos_teste, n_teste);
    int resultado_dp = cut_rod_dp(precos_teste, n_teste);
    
    printf("Teste n=5:\n");
    printf("Greedy: %d\n", resultado_greedy);
    printf("DP: %d\n", resultado_dp);
    printf("Diferença: %.2f%%\n", 
           100.0 * resultado_greedy / resultado_dp);
}

/**
 * Estrutura para armazenar um resultado
 */
typedef struct {
    int n;
    int v_dp;
    double t_dp;
    int v_greedy;
    double t_greedy;
    double porcentagem;
} Resultado;

/**
 * Salva resultados em arquivo texto
 */

void salva_resultados(Resultado* resultados, int num_resultados, const char* arquivo) {
    FILE* f = fopen(arquivo, "w");
    if (!f) return;

    fprintf(f, "%7s %10s %12s %10s %12s %10s\n",
            "n", "vDP", "tDP", "vGreedy", "tGreedy", "%");
    fprintf(f, "--------------------------------------------------------\n");

    for (int i = 0; i < num_resultados; i++) {
        Resultado r = resultados[i];
        fprintf(f, "%7d %10d %12.6f %10d %12.6f %9.2f%%\n",
                r.n, r.v_dp, r.t_dp, r.v_greedy, r.t_greedy, r.porcentagem);
    }
    fclose(f);
}

/**
 * Loop principal do programa
 */

int main() {
    srand(time(NULL));

    int num_resultados = (FIM - INC) / STP + 1;
    Resultado* resultados = (Resultado*)malloc(num_resultados * sizeof(Resultado));
    if (!resultados) {
        printf("Erro: falha na alocação de memória\n");
        return 1;
    }

    printf("\n%7s %10s %12s %10s %12s %10s\n", 
           "n", "vDP", "tDP", "vGreedy", "tGreedy", "%");
    printf("--------------------------------------------------------\n");

    int idx = 0;
    for (int n = INC; n <= FIM; n += STP) {
        // Gera preços para tamanho n
        int* precos = gera_precos(n);
        if (!precos) continue;

        Resultado r = {.n = n};
        clock_t inicio = clock();
        r.v_dp = cut_rod_dp(precos, n);
        clock_t fim = clock();
        r.t_dp = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        inicio = clock();
        r.v_greedy = cut_rod_greedy(precos, n);
        fim = clock();
        r.t_greedy = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        r.porcentagem = (r.v_dp > 0) ? 
            (100.0 * r.v_greedy / r.v_dp) : 0.0;
        resultados[idx++] = r;
        printf("%7d %10d %12.6f %10d %12.6f %9.2f%%\n",
               r.n, r.v_dp, r.t_dp, r.v_greedy, r.t_greedy, r.porcentagem);

        free(precos);
    }

    // Análise dos resultados
    double media_porcentagem = 0.0;
    for (int i = 0; i < idx; i++) {
        media_porcentagem += resultados[i].porcentagem;
    }
    media_porcentagem /= idx;

    printf("\nResumo:\n");
    printf("Média das porcentagens: %.2f%%\n", media_porcentagem);
    salva_resultados(resultados, idx, "resultados.txt");

    free(resultados);
    return 0;
}