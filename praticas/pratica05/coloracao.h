#ifndef COLORACAO_H
#define COLORACAO_H

#include <stdbool.h>

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    int num_vertices;
    int num_arestas;
    No **lista_adj;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
bool eh_bipartido(GrafoLista *g);

#endif