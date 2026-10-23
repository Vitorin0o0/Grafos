#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include <stdbool.h>

// Estrutura de Grafo (Matriz de Adjacência)
typedef struct {
    int num_vertices;
    int **matriz;
} Grafo;

// Funções básicas do Grafo
Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo *g, int u, int v, int peso);
void liberar_grafo(Grafo *g);
Grafo* gerar_grafo_aleatorio(int num_vertices, double prob);

// Funções para Caminho e Ciclo Hamiltoniano
bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho);
bool encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo);

#endif 