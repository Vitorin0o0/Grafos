#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

GrafoLista* criar_grafo(int num_vertices) {

    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->adj = (No**) malloc(num_vertices * sizeof(No*));

    for (int i = 0; i < num_vertices; i++) {

        g->adj[i] = NULL;
    }

    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {

    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = g->adj[v];
    g->adj[v] = novo;

    g->num_arestas++;
}

void liberar_grafo(GrafoLista *g) {

    for (int i = 0; i < g->num_vertices; i++) {

        No *atual = g->adj[i];

        while (atual != NULL) {

            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->adj);
    free(g);
}

// algoritmo Tarjan
void dfs_articulacoes(GrafoLista *g, int u, int *tempo, int descoberta[], int low[], int pai[], int e_articulacao[]) {

    int filhos = 0;
    descoberta[u] = low[u] = ++(*tempo);

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->vertice;

        if (descoberta[v] == -1) {
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, tempo, descoberta, low, pai, e_articulacao);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (pai[u] == -1 && filhos > 1) {
                e_articulacao[u] = 1;
            }
            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                e_articulacao[u] = 1;
            }

            if (low[v] > descoberta[u]) {
                printf("  [Ponte detectada] Aresta: (%d, %d)\n", u, v);
            }
        } else if (v != pai[u]) {
            low[u] = (low[u] < descoberta[v]) ? low[u] : descoberta[v];
        }
    }
}

void detectar_pontes_e_articulacoes(GrafoLista *g) {

    int n = g->num_vertices;
    int *descoberta = (int*) malloc(n * sizeof(int));
    int *low = (int*) malloc(n * sizeof(int));
    int *pai = (int*) malloc(n * sizeof(int));
    int *e_articulacao = (int*) malloc(n * sizeof(int));
    int tempo = 0;

    for (int i = 0; i < n; i++) {

        descoberta[i] = -1;
        low[i] = -1;
        pai[i] = -1;
        e_articulacao[i] = 0;
    }

    printf("--- Análise de Conectividade (Algoritmo de Tarjan) ---\n");

    for (int i = 0; i < n; i++) {

        if (descoberta[i] == -1) {

            dfs_articulacoes(g, i, &tempo, descoberta, low, pai, e_articulacao);
        }
    }

    printf("Vértices de corte (Articulações): ");
    int encontrou = 0;

    for (int i = 0; i < n; i++) {

        if (e_articulacao[i]) {

            printf("%d ", i);
            encontrou = 1;
        }
    }
    
    if (!encontrou) printf("Nenhum");
    printf("\n");

    free(descoberta);
    free(low);
    free(pai);
    free(e_articulacao);
}