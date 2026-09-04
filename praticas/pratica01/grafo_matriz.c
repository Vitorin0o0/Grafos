#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_matriz.h"

void criar_grafo_matriz(GrafoMatriz *grafo, int n) {

    grafo->n = n;

    grafo->adj = (int **) malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {

        grafo->adj[i] = (int *) calloc(n, sizeof(int));
    }
}

void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v) {

    grafo->adj[u][v] = 1;
    grafo->adj[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v) {

    grafo->adj[u][v] = 0;
    grafo->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz *grafo, int v) {
    int grau = 0;

    for (int j = 0; j < grafo->n; j++) {

        if (grafo->adj[v][j] == 1) {

            grau++;
        }
    }

    return grau;
}

void sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v) {

    if (grafo->adj[u][v]) {

        printf("Sim, tais vértices são adjacentes.\n");
    } else {

        printf("Não, tais vértices não são adjacentes.\n");
    }
}

void liberar_grafo_matriz(GrafoMatriz *grafo) {

    if (grafo == NULL || grafo->adj == NULL) return;

    for (int i = 0; i < grafo->n; i++) {

        free(grafo->adj[i]);
    }

    free(grafo->adj);
    
    grafo->adj = NULL;
    grafo->n = 0;
}