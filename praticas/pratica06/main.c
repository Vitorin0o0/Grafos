#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int num_vertices = 5;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1, 10);
    adicionar_aresta(g, 0, 4, 3);
    adicionar_aresta(g, 1, 2, 2);
    adicionar_aresta(g, 1, 4, 4);
    adicionar_aresta(g, 2, 3, 9);
    adicionar_aresta(g, 3, 2, 7);
    adicionar_aresta(g, 4, 1, 1);
    adicionar_aresta(g, 4, 2, 8);
    adicionar_aresta(g, 4, 3, 2);

    int origem = 0;
    int *dist = (int*) malloc(num_vertices * sizeof(int));
    int *pred = (int*) malloc(num_vertices * sizeof(int));

    dijkstra(g, origem, dist, pred);

    printf("Distancias a partir da origem %d:\n", origem);

    for (int i = 0; i < num_vertices; i++){
        
        printf("Para %d: %d\n", i, dist[i]);
    }

    printf("\nCaminhos minimos:\n");

    for (int i = 0; i < num_vertices; i++){

        if (i != origem) {
            printf("Caminho 0 -> %d: ", i);
            reconstruir_caminho(origem, i, pred);
            printf("\n");
        }
    }

    free(dist);
    free(pred);
    liberar_grafo(g);

    return 0;
}