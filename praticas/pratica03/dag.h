#ifndef DAG_H
#define DAG_H
#include <stdbool.h>

typedef struct No {
    int vertice;
    struct No* prox;
} No;


typedef struct {
    int num_vertices;
    No** adjacencias;
} GrafoLista;

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
bool eh_dag(GrafoLista *g);

// Funções de auxilio
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista* g, int origem, int destino);
void liberar_grafo(GrafoLista* g);

#endif