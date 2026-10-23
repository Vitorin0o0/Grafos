#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

void imprimir_caminho(int *caminho, int n, bool eh_ciclo) {
    for (int i = 0; i < n; i++) {
        printf("%d ", caminho[i]);
        if (i < n - 1) printf("-> ");
    }
    if (eh_ciclo) printf(" -> %d", caminho[0]);
    printf("\n");
}

void executar_experimento(int n) {
    printf("=======================================\n");
    printf("Testando Grafo com %d vertices\n", n);
    
    // Probabilidade de 0.7 para aumentar as chances de existir um caminho hamiltoniano
    Grafo *g = gerar_grafo_aleatorio(n, 0.7);
    Grafo *tsp_g = grafo_para_tsp(g);

    int *caminho = (int*) malloc(n * sizeof(int));
    
    // Testes de Caminho e Ciclo Hamiltoniano
    printf("--- Buscas Hamiltonianas ---\n");
    if (encontrar_caminho_hamiltoniano_bt(g, caminho)) {
        printf("Caminho Hamiltoniano: Encontrado (");
        imprimir_caminho(caminho, n, false);
        printf(")");
    } else {
        printf("Caminho Hamiltoniano: Nao encontrado.\n");
    }

    if (encontrar_ciclo_hamiltoniano_bt(g, caminho)) {
        printf("Ciclo Hamiltoniano  : Encontrado (");
        imprimir_caminho(caminho, n, true);
        printf(")");
    } else {
        printf("Ciclo Hamiltoniano  : Nao encontrado.\n");
    }

    // Testes do TSP
    printf("\n--- Problema do Caixeiro Viajante (TSP) ---\n");
    
    clock_t inicio_fb = clock();
    int custo_fb = tsp_forca_bruta(tsp_g, 0, caminho);
    clock_t fim_fb = clock();
    double tempo_fb = (double)(fim_fb - inicio_fb) / CLOCKS_PER_SEC;

    clock_t inicio_vmp = clock();
    int custo_vmp = tsp_vizinho_mais_proximo(tsp_g, 0, caminho);
    clock_t fim_vmp = clock();
    double tempo_vmp = (double)(fim_vmp - inicio_vmp) / CLOCKS_PER_SEC;

    clock_t inicio_ins = clock();
    int custo_ins = tsp_insercao(tsp_g, 0, caminho);
    clock_t fim_ins = clock();
    double tempo_ins = (double)(fim_ins - inicio_ins) / CLOCKS_PER_SEC;

    printf("Forca Bruta         : Custo = %d | Tempo = %.6f s\n", custo_fb, tempo_fb);
    printf("Vizinho Mais Proximo: Custo = %d | Tempo = %.6f s\n", custo_vmp, tempo_vmp);
    printf("Insercao Mais Prox. : Custo = %d | Tempo = %.6f s\n", custo_ins, tempo_ins);

    free(caminho);
    liberar_grafo(g);
    liberar_grafo(tsp_g);
}

int main() {
    srand(42); 
    int tamanhos[] = {5, 8, 10, 12};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("Iniciando Experimentos (Hamiltoniano e TSP)...\n");
    for (int i = 0; i < num_testes; i++) {
        executar_experimento(tamanhos[i]);
    }
    return 0;
}