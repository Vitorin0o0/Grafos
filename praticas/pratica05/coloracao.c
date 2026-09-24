#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coloracao.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->lista_adj = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->lista_adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->proximo = g->lista_adj[u];
    g->lista_adj[u] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vertice = u;
    novo->proximo = g->lista_adj[v];
    g->lista_adj[v] = novo;

    g->num_arestas++;
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista_adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->lista_adj);
    free(g);
}

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {

    int v = g->num_vertices;
    int *cor = (int*) malloc(v * sizeof(int));
    bool *disponivel = (bool*) malloc(v * sizeof(bool));

    for (int i = 0; i < v; i++) {

        cor[i] = -1;
        disponivel[i] = true;
    }

    cor[0] = 0;

    for (int u = 1; u < v; u++) {

        No *p = g->lista_adj[u];

        while (p != NULL) {

            if (cor[p->vertice] != -1) {

                disponivel[cor[p->vertice]] = false;
            }

            p = p->proximo;
        }

        int cr;

        for (cr = 0; cr < v; cr++) {

            if (disponivel[cr]) break;
        }

        cor[u] = cr;

        p = g->lista_adj[u];

        while (p != NULL) {

            if (cor[p->vertice] != -1) {

                disponivel[cor[p->vertice]] = true;
            }
            p = p->proximo;
        }
    }

    int max_cor = 0;

    for (int i = 0; i < v; i++) {
        
        if (cor[i] > max_cor) max_cor = cor[i];
    }
    *num_cores = max_cor + 1;

    free(disponivel);
    return cor;
}

typedef struct {
    int id;
    int grau;
} VerticeGrau;

static int comparar_graus(const void *a, const void *b) {
    VerticeGrau *v1 = (VerticeGrau*) a;
    VerticeGrau *v2 = (VerticeGrau*) b;
    return v2->grau - v1->grau;
}

// Heurística Welsh-Powell 
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int v = g->num_vertices;
    VerticeGrau *vertices = (VerticeGrau*) malloc(v * sizeof(VerticeGrau));

    for (int i = 0; i < v; i++) {

        vertices[i].id = i;
        vertices[i].grau = 0;
        No *p = g->lista_adj[i];
        while (p != NULL) {
            vertices[i].grau++;
            p = p->proximo;
        }
    }

    qsort(vertices, v, sizeof(VerticeGrau), comparar_graus);

    int *cor = (int*) malloc(v * sizeof(int));
    bool *disponivel = (bool*) malloc(v * sizeof(bool));

    for (int i = 0; i < v; i++) {

        cor[i] = -1;
        disponivel[i] = true;
    }

    for (int i = 0; i < v; i++) {

        int u = vertices[i].id;

        No *p = g->lista_adj[u];

        while (p != NULL) {

            if (cor[p->vertice] != -1) {
                disponivel[cor[p->vertice]] = false;
            }
            p = p->proximo;
        }

        int cr;

        for (cr = 0; cr < v; cr++) {

            if (disponivel[cr]) break;
        }

        cor[u] = cr;

        p = g->lista_adj[u];

        while (p != NULL) {

            if (cor[p->vertice] != -1) {
                disponivel[cor[p->vertice]] = true;
            }
            p = p->proximo;
        }
    }

    int max_cor = 0;

    for (int i = 0; i < v; i++) {
        if (cor[i] > max_cor) max_cor = cor[i];
    }

    *num_cores = max_cor + 1;

    free(vertices);
    free(disponivel);
    return cor;
}

bool eh_bipartido(GrafoLista *g) {

    int v = g->num_vertices;
    int *cor = (int*) malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) cor[i] = -1;

    int *fila = (int*) malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {

        if (cor[i] == -1) {
            cor[i] = 0;
            int inicio = 0, fim = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];
                No *p = g->lista_adj[u];

                while (p != NULL) {
                    int vizinho = p->vertice;
                    if (cor[vizinho] == -1) {
                        cor[vizinho] = 1 - cor[u];
                        fila[fim++] = vizinho;
                    } else if (cor[vizinho] == cor[u]) {
                        free(cor);
                        free(fila);
                        return false;
                    }
                    p = p->proximo;
                }
            }
        }
    }

    free(cor);
    free(fila);
    return true;
}