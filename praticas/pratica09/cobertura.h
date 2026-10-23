#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Estrutura de Grafo 
typedef struct {
    int num_vertices;
    int **matriz;
} Grafo;

// Funções do Grafo
Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo *g, int u, int v);
void liberar_grafo(Grafo *g);
Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade_aresta);

// Funções do Algoritmo
bool eh_cobertura(Grafo *g, int *cobertura);
int cobertura_minima_bt(Grafo *g, int *melhor_cobertura);
int cobertura_gulosa(Grafo *g, int *cobertura);

#endif