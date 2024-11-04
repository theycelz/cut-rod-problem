#include "rod_cutting.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h> 
#include <sys/types.h>

static int compara_densidade(const void* a, const void* b) {
    DensidadeInfo* d1 = (DensidadeInfo*)a;
    DensidadeInfo* d2 = (DensidadeInfo*)b;
    if (d1->densidade < d2->densidade) return 1;
    if (d1->densidade > d2->densidade) return -1;
    return 0;
}

int* gera_precos(int n) {
    if (n <= 0) return NULL;

    int* precos = (int*)malloc(n * sizeof(int));
    if (!precos) return NULL;

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
            double position_factor = (n > 0) ? (double)i / n : 0; // Verificação para evitar divisão por zero
            int extra_increment = (int)(position_factor * 5);
            precos[i] = precos[i-1] + base_increment + extra_increment;
        }

        if (precos[i] > n) precos[i] = n;
        if (precos[i] <= precos[i-1]) precos[i] = precos[i-1] + 1;
    }

    for (int i = n/4; i < n; i += n/4) {
        int valley_size = 3 + (rand() % 5);
        for (int j = 0; j < valley_size && (i+j) < n; j++) {
            double current_density = (i + j + 1) != 0 ? (double)precos[i+j] / (i+j+1) : 0.0; // Evita divisão por zero
            double target_density = current_density * 0.7;
            int new_price = (int)(target_density * (i+j+1));

            if (new_price > precos[i+j-1] && new_price <= n) {
                precos[i+j] = new_price;
            }
        }
    }

    return precos;
}

int cut_rod_dp(int* precos, int n) {
    if (!precos || n < 0) return -1;

    int* rod = (int*)malloc((n + 1) * sizeof(int));
    if (!rod) return -1;

    rod[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = precos[i-1];
        for (int j = 1; j < i; j++) {
            int val = precos[j-1] + rod[i-j];
            if (val > max_val) max_val = val;
        }
        rod[i] = max_val;
    }

    int resultado = rod[n];
    free(rod);
    return resultado;
}

int cut_rod_greedy(int* precos, int n) {
    if (!precos || n <= 0) return -1;

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

void testa_dp() {
    int precos_teste[] = {1, 5, 8, 9, 10};
    int n_teste = 5;
    int resultado = cut_rod_dp(precos_teste, n_teste);
    printf("Teste DP n=5: %d (esperado: 13)\n", resultado);
    printf("Teste null: %d (esperado: -1)\n", cut_rod_dp(NULL, 5));
    printf("Teste n negativo: %d (esperado: -1)\n", cut_rod_dp(precos_teste, -1));
}

void testa_greedy() {
    int precos_teste[] = {1, 5, 8, 9, 10};
    int n_teste = 5;

    int resultado_greedy = cut_rod_greedy(precos_teste, n_teste);
    int resultado_dp = cut_rod_dp(precos_teste, n_teste);

    printf("Teste n=5:\n");
    printf("Greedy: %d\n", resultado_greedy);
    printf("DP: %d\n", resultado_dp);
    printf("Diferença: %.2f%%\n", 100.0 * resultado_greedy / resultado_dp);
}

void salva_resultados(Resultado* resultados, int num_resultados, const char* arquivo) {
    char script_dir[1024];
    realpath(arquivo, script_dir);
    char* last_slash = strrchr(script_dir, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';
    }
    char data_dir[2048];
    snprintf(data_dir, sizeof(data_dir), "%s/../data", script_dir);
    mkdir(data_dir, 0777);
    char filepath[4096];
    snprintf(filepath, sizeof(filepath), "%s/resultados.txt", data_dir);
    
    FILE* f = fopen(filepath, "w");
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
