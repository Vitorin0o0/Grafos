#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main(){
    
    int V = 5;
    int E = 7;
    GrafoLista *g = criar_grafo(V);
    Aresta *arestas = (Aresta*) malloc(E * sizeof(Aresta));
    int idx_aresta = 0;

    adicionar_aresta(g, arestas, &idx_aresta, 0, 1, 2);
    adicionar_aresta(g, arestas, &idx_aresta, 0, 3, 6);
    adicionar_aresta(g, arestas, &idx_aresta, 1, 2, 3);
    adicionar_aresta(g, arestas, &idx_aresta, 1, 3, 8);
    adicionar_aresta(g, arestas, &idx_aresta, 1, 4, 5);
    adicionar_aresta(g, arestas, &idx_aresta, 2, 4, 7);
    adicionar_aresta(g, arestas, &idx_aresta, 3, 4, 9);

    printf("=== Algoritmo de Kruskal ===\n");
    kruskal(arestas, E, V);
    printf("\n");

    printf("=== Algoritmo de Prim ===\n");
    prim(g, 0);
    
    free(arestas);
    liberar_grafo(g);

    return 0;
}