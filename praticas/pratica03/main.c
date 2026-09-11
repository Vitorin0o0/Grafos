#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int main() {
    

    GrafoLista* g = criar_grafo(6);
    adicionar_aresta(g, 5, 2);
    adicionar_aresta(g, 5, 0);
    adicionar_aresta(g, 4, 0);
    adicionar_aresta(g, 4, 1);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 1);

    printf("Verificando se o grafo e um DAG...\n");
    if (eh_dag(g)) {
        printf("Resultado: O grafo eh um DAG (Aciclico).\n\n");
    } else {
        printf("Resultado: O grafo NAO eh um DAG (Possui ciclo).\n\n");
    }

    int tamanho = 0;

    printf("--- Ordenacao Topologica (Kahn) ---\n");
    int* ordem_kahn = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem_kahn != NULL) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", ordem_kahn[i]);
        }
        printf("\n\n");
        free(ordem_kahn);
    } else {
        printf("Erro: Grafo possui ciclo.\n\n");
    }

    printf("--- Ordenacao Topologica (DFS) ---\n");
    int* ordem_dfs = ordenacao_topologica_dfs(g, &tamanho);
    if (ordem_dfs != NULL) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", ordem_dfs[i]);
        }
        printf("\n\n");
        free(ordem_dfs);
    } else {
        printf("Erro: Grafo possui ciclo.\n\n");
    }

    liberar_grafo(g);
    return 0;
}