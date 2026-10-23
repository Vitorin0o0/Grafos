#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

void executar_experimento(int n){

    Grafo *g = gerar_grafo_aleatorio(n, 0.4); 
    
    int *cobertura_bt = (int*) calloc(n, sizeof(int));
    int *cobertura_gulosa_arr = (int*) calloc(n, sizeof(int));

    printf("=======================================\n");
    printf("Testando Grafo com %d vertices\n", n);
    
    // Teste Backtracking
    clock_t inicio_bt = clock();
    int tam_bt = cobertura_minima_bt(g, cobertura_bt);
    clock_t fim_bt = clock();
    double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;

    // Teste Guloso
    clock_t inicio_guloso = clock();
    int tam_guloso = cobertura_gulosa(g, cobertura_gulosa_arr);
    clock_t fim_guloso = clock();
    double tempo_guloso = (double)(fim_guloso - inicio_guloso) / CLOCKS_PER_SEC;

    printf("Backtracking: Tamanho = %d | Tempo = %.6f segundos\n", tam_bt, tempo_bt);
    printf("Guloso      : Tamanho = %d | Tempo = %.6f segundos\n", tam_guloso, tempo_guloso);
    
    free(cobertura_bt);
    free(cobertura_gulosa_arr);
    liberar_grafo(g);
}

int main(){
    
    srand(42); 

    int tamanhos[] = {5, 8, 10, 12, 15};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("Iniciando Experimentos de Cobertura de Vertices...\n");
    
    for (int i = 0; i < num_testes; i++){

        executar_experimento(tamanhos[i]);
    }

    return 0;
}