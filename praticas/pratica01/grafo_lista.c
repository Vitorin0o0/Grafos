#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

void criar_grafo_lista(GrafoLista *grafo, int n) {

    grafo->n = n;

    grafo->adj = (No **) malloc(n * sizeof(No *));

    for (int i = 0; i < n; i++) {

        grafo->adj[i] = NULL;
    }
}

void inserir_aresta_lista(GrafoLista *grafo, int u, int v) {

    
    No *novo1 = (No *) malloc(sizeof(No));
    novo1->destino = v;
    novo1->prox = grafo->adj[u];
    grafo->adj[u] = novo1;


    No *novo2 = (No *) malloc(sizeof(No));
    novo2->destino = u;
    novo2->prox = grafo->adj[v];
    grafo->adj[v] = novo2;
}

void remover_aresta_lista(GrafoLista *grafo, int u, int v) {
    
    No *atual = grafo->adj[u];
    No *anterior = NULL;

    while (atual != NULL && atual->destino != v) {

        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {

        if (anterior == NULL) {

            grafo->adj[u] = atual->prox;
        } else {

            anterior->prox = atual->prox;
        }

        free(atual);
    }


    atual = grafo->adj[v];
    anterior = NULL;

    while (atual != NULL && atual->destino != u) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) { 
        if (anterior == NULL) {
            grafo->adj[v] = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

int grau_lista(GrafoLista *grafo, int v) {
    int grau = 0;
    No *atual = grafo->adj[v];

    // Percorre a lista do vértice v contando os nós
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }

    return grau;
}

void sao_adjacentes_lista(GrafoLista *grafo, int u, int v) {
    No *atual = grafo->adj[u];

    while (atual != NULL) {

        if (atual->destino == v) {

            printf("Sim, tais vértices são adjacentes.\n");
            return;
        }

        atual = atual->prox;
    }

    printf("Não, tais vértices não são adjacentes.\n");
}

void liberar_grafo_lista(GrafoLista *grafo) {

    if (grafo == NULL || grafo->adj == NULL) return;

    for (int i = 0; i < grafo->n; i++) {

        No *atual = grafo->adj[i];

        while (atual != NULL) {
            
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(grafo->adj);

    grafo->adj = NULL;
    grafo->n = 0;
}