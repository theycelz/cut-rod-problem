#include "rod_cutting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INC 1000  
#define FIM 20000 
#define STP 1000  

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
        
        r.porcentagem = (r.v_dp > 0) ? (100.0 * r.v_greedy / r.v_dp) : 0.0;
        resultados[idx++] = r;

        printf("%7d %10d %12.6f %10d %12.6f %9.2f%%\n",
               r.n, r.v_dp, r.t_dp, r.v_greedy, r.t_greedy, r.porcentagem);

        free(precos);
    }

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