#ifndef AGM_H
#define AGM_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ================= ESTRUTURAS DO DSU (Union-Find) ================= //
typedef struct {
    int *pai, *rank;
    int n;
} DSU;

// ================= ESTRUTURA DE ARESTA (Kruskal) ================= //
typedef struct {
    int u, v, peso;
} Aresta;

// ================= ESTRUTURAS DO GRAFO (Lista de Adjacência para Prim) ================= //
typedef struct NoAdj {
    int destino;
    int peso;
    struct NoAdj *prox;
} NoAdj;

typedef struct {
    NoAdj *cabeca;
} ListaAdj;

typedef struct {
    int num_vertices;
    ListaAdj *vetor_listas;
} GrafoLista;

// ================= ESTRUTURAS DO MIN-HEAP (Prim) ================= //
typedef struct {
    int vertice;
    int chave; // Peso mínimo da aresta conectando à árvore
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

// ================= PROTÓTIPOS DAS FUNÇÕES ================= //

// Funções DSU
DSU* criar_dsu(int n);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void liberar_dsu(DSU *d);

// Funções Grafo
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, Aresta *arestas, int *idx_aresta, int u, int v, int peso);
void liberar_grafo(GrafoLista *g);

// Algoritmos de Árvore Geradora Mínima
void kruskal(Aresta *arestas, int E, int V);
void prim(GrafoLista *g, int origem);

#endif