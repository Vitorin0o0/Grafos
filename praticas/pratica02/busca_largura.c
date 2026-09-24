#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

Fila* criar_fila(int capacidade){

    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->capacidade = capacidade;
    f->dados = (int*) malloc(capacidade * sizeof(int));
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
    return f;
}

void destruir_fila(Fila *f){

    if (f) {
        free(f->dados);
        free(f);
    }
}

int fila_vazia(Fila *f) {

    return f->tamanho == 0;
}

void enfileirar(Fila *f, int v){

    if (f->tamanho == f->capacidade) return;
    f->fim = (f->fim + 1) % f->capacidade;
    f->dados[f->fim] = v;
    f->tamanho++;
}

int desenfileirar(Fila *f){

    if (fila_vazia(f)) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred){

    for (int i = 0; i < g->num_vertices; i++) {

        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->num_vertices);

    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)){

        int u = desenfileirar(f);

        No *atual = g->listas_adj[u];
        while (atual != NULL) {

            int v = atual->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }

            atual = atual->prox;
        }
    }

    destruir_fila(f);
}

int eh_bipartido(GrafoLista *g){

    int *cor = (int*) malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) cor[i] = -1;

    Fila *f = criar_fila(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] == -1) {
            cor[i] = 0;
            enfileirar(f, i);

            while (!fila_vazia(f)) {
                int u = desenfileirar(f);

                No *atual = g->listas_adj[u];
                while (atual != NULL) {

                    int v = atual->vertice;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        destruir_fila(f);
                        return 0; 
                    }
                    atual = atual->prox;
                }
            }
        }
    }

    free(cor);
    destruir_fila(f);
    return 1; 
}