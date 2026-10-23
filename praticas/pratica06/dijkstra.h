#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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

// Estruturas do Min-Heap 
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; 
} MinHeap;

// Funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Funções do Min-Heap 
MinHeap* criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);
void liberar_min_heap(MinHeap *heap);
int heap_vazio(MinHeap *heap);

// Funções do Algoritmo 
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif 