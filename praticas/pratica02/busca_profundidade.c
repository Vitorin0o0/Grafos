#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha* criar_pilha(int capacidade){

    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->capacidade = capacidade;
    p->dados = (int*) malloc(capacidade * sizeof(int));
    p->topo = -1;
    return p;
}

void destruir_pilha(Pilha *p){

    if (p){
        free(p->dados);
        free(p);
    }
}

int pilha_vazia(Pilha *p){

    return p->topo == -1;
}

void empilhar(Pilha *p, int v){

    if (p->topo < p->capacidade - 1){
        p->dados[++(p->topo)] = v;
    }
}

int desempilhar(Pilha *p){

    if (pilha_vazia(p)) return -1;
    return p->dados[(p->topo)--];
}

void dfs_recursiva_aux(GrafoLista *g, int u, int *visitado, int *pred){

    visitado[u] = 1;
    No *atual = g->listas_adj[u];

    while (atual != NULL){

        int v = atual->vertice;

        if (!visitado[v]){

            pred[v] = u;
            dfs_recursiva_aux(g, v, visitado, pred);
        }
        atual = atual->prox;
    }
}

void dfs_recursiva(GrafoLista *g, int origem, int *visitado, int *pred){

    for (int i = 0; i < g->num_vertices; i++){

        visitado[i] = 0;
        pred[i] = -1;
    }

    dfs_recursiva_aux(g, origem, visitado, pred);
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado){

    for (int i = 0; i < g->num_vertices; i++) visitado[i] = 0;

    Pilha *p = criar_pilha(g->num_vertices);
    empilhar(p, origem);

    while (!pilha_vazia(p)) {

        int u = desempilhar(p);

        if (!visitado[u]){
            visitado[u] = 1;

            No *atual = g->listas_adj[u];
            while (atual != NULL){
                int v = atual->vertice;
                if (!visitado[v]){
                    empilhar(p, v);
                }
                atual = atual->prox;
            }
        }
    }

    destruir_pilha(p);
}

int contar_componentes(GrafoLista *g){

    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    int *pred = (int*) malloc(g->num_vertices * sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->num_vertices; i++){

        if (!visitado[i]){
            componentes++;
            dfs_recursiva_aux(g, i, visitado, pred);
        }
    }

    free(visitado);
    free(pred);
    return componentes;
}

static int tem_ciclo_aux(GrafoLista *g, int u, int *visitado, int pai){

    visitado[u] = 1;
    No *atual = g->listas_adj[u];

    while (atual != NULL){

        int v = atual->vertice;
        if (!visitado[v]){
            if (tem_ciclo_aux(g, v, visitado, u)) return 1;
        } else if (v != pai){
            return 1; 
        }
        atual = atual->prox;
    }
    return 0;
}

int tem_ciclo(GrafoLista *g){

    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));

    for (int i = 0; i < g->num_vertices; i++) {

        if (!visitado[i]){

            if (tem_ciclo_aux(g, i, visitado, -1)){
                free(visitado);
                return 1;
            }
        }
    }

    free(visitado);
    return 0;
}