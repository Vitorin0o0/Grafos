#include <stdio.h>
#include <stdlib.h>
#include "dag.h"


GrafoLista* criar_grafo(int num_vertices) {

    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adjacencias = (No**)malloc(num_vertices * sizeof(No*));

    for (int i = 0; i < num_vertices; i++) {

        g->adjacencias[i] = NULL;
    }

    return g;
}

void adicionar_aresta(GrafoLista* g, int origem, int destino) {

    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->vertice = destino;
    novo_no->prox = g->adjacencias[origem];
    g->adjacencias[origem] = novo_no;
}

void liberar_grafo(GrafoLista* g) {

    for (int i = 0; i < g->num_vertices; i++) {

        No* atual = g->adjacencias[i];

        while (atual != NULL) {

            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->adjacencias);
    free(g);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {

    int n = g->num_vertices;
    int* grau_entrada = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {

        No* atual = g->adjacencias[i];

        while (atual != NULL) {

            grau_entrada[atual->vertice]++;
            atual = atual->prox;
        }
    }

    int* fila = (int*)malloc(n * sizeof(int));
    int inicio = 0, fim = 0;

    for (int i = 0; i < n; i++) {

        if (grau_entrada[i] == 0) {

            fila[fim++] = i;
        }
    }

    int* resultado = (int*)malloc(n * sizeof(int));
    int count = 0;

    while (inicio < fim) {

        int u = fila[inicio++];
        resultado[count++] = u;

        No* atual = g->adjacencias[u];

        while (atual != NULL) {

            int v = atual->vertice;
            grau_entrada[v]--;

            if (grau_entrada[v] == 0) {

                fila[fim++] = v;
            }

            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    if (count != n) {

        free(resultado);
        *tamanho = 0;
        return NULL; 
    }

    *tamanho = count;
    return resultado;
}

void dfs_visitar_topologico(GrafoLista *g, int u, int *visitado, int *pilha, int *topo) {

    visitado[u] = 1;
    No* atual = g->adjacencias[u];
    
    while (atual != NULL) {

        int v = atual->vertice;
        if (!visitado[v]) {
            dfs_visitar_topologico(g, v, visitado, pilha, topo);
        }
        atual = atual->prox;
    }

    pilha[(*topo)++] = u;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {

    if (!eh_dag(g)) {

        *tamanho = 0;
        return NULL; 
    }

    int n = g->num_vertices;
    int* visitado = (int*)calloc(n, sizeof(int));
    int* pilha = (int*)malloc(n * sizeof(int));
    int topo = 0;

    for (int i = 0; i < n; i++) {

        if (!visitado[i]) {
            dfs_visitar_topologico(g, i, visitado, pilha, &topo);
        }
    }

    int* resultado = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {

        resultado[i] = pilha[n - 1 - i];
    }

    free(visitado);
    free(pilha);
    
    *tamanho = n;
    return resultado;
}

bool dfs_tem_ciclo(GrafoLista *g, int u, int *cor) {

    cor[u] = 1;     
    No* atual = g->adjacencias[u];

    while (atual != NULL) {

        int v = atual->vertice;

        if (cor[v] == 1) {
            return true; 
        }
        if (cor[v] == 0 && dfs_tem_ciclo(g, v, cor)) {
            return true;
        }
        atual = atual->prox;
    }
    
    cor[u] = 2; 
    return false;
}

bool eh_dag(GrafoLista *g) {

    int n = g->num_vertices;
    int* cor = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {

        if (cor[i] == 0) {
            if (dfs_tem_ciclo(g, i, cor)) {
                
                free(cor);
                return false; // Tem ciclo, logo não é DAG
            }
        }
    }
    
    free(cor);
    return true; // É DAG
}