#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

void testar_grafo_sem_ciclo_negativo(){

    printf("=== Teste 1: Grafo SEM ciclo negativo ===\n");
    int V = 5;
    GrafoListaPonderado *g = criar_grafo(V);

    adicionar_aresta(g, 0, 1, -1);
    adicionar_aresta(g, 0, 2, 4);
    adicionar_aresta(g, 1, 2, 3);
    adicionar_aresta(g, 1, 3, 2);
    adicionar_aresta(g, 1, 4, 2);
    adicionar_aresta(g, 3, 2, 5);
    adicionar_aresta(g, 3, 1, 1);
    adicionar_aresta(g, 4, 3, -3);

    int *dist = (int *) malloc(V * sizeof(int));
    int *pred = (int *) malloc(V * sizeof(int));
    int vertice_ciclo = -1;

    if (bellman_ford(g, 0, dist, pred, &vertice_ciclo)){

        printf("Distancias a partir da origem 0:\n");
        for (int i = 0; i < V; i++) {
            printf("Para %d: %d\n", i, dist[i]);
        }
    } else{

        printf("Erro: Ciclo negativo encontrado onde nao deveria existir.\n");
    }

    free(dist); free(pred);
    liberar_grafo(g);
    printf("\n");
}

void testar_grafo_com_ciclo_negativo(){
    
    printf("=== Teste 2: Grafo com ciclo negativo ===\n");
    int V = 4;
    GrafoListaPonderado *g = criar_grafo(V);

    adicionar_aresta(g, 0, 1, 1);
    adicionar_aresta(g, 1, 2, -1);
    adicionar_aresta(g, 2, 3, -1);
    adicionar_aresta(g, 3, 1, -1); 

    int *dist = (int *) malloc(V * sizeof(int));
    int *pred = (int *) malloc(V * sizeof(int));
    int vertice_ciclo = -1;

    if (!bellman_ford(g, 0, dist, pred, &vertice_ciclo)) {
        reconstruir_ciclo_negativo(vertice_ciclo, pred, V);
    } else {
        printf("Erro: Algoritmo falhou em detectar o ciclo negativo.\n");
    }

    free(dist); free(pred);
    liberar_grafo(g);
    printf("\n");
}

int main(){

    testar_grafo_sem_ciclo_negativo();
    testar_grafo_com_ciclo_negativo();
    return 0;
}