#ifndef ROD_CUTTING_H
#define ROD_CUTTING_H

typedef struct {
    double densidade;
    int indice;
} DensidadeInfo;

typedef struct {
    int n;
    int v_dp;
    double t_dp;
    int v_greedy;
    double t_greedy;
    double porcentagem;
} Resultado;

// Funções principais
int* gera_precos(int n);
int cut_rod_dp(int* precos, int n);
int cut_rod_greedy(int* precos, int n);

// Funções de teste
void testa_dp(void);
void testa_greedy(void);

// Funções de resultado
void salva_resultados(Resultado* resultados, int num_resultados, const char* arquivo);

#endif