#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estruturas do Grafo Ponderado com Lista de Adjacência
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    Aresta *cabeca;
} ListaAdj;

typedef struct {
    int num_vertices;
    ListaAdj *vetor_listas;
} GrafoListaPonderado;

// Funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Funções do Algoritmo
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred, int *vertice_ciclo);
void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int num_vertices);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif