#include "hamiltoniano.h"
#include <stdlib.h>
#include <stdio.h>

Grafo* criar_grafo(int num_vertices) {

    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->matriz = (int**) malloc(num_vertices * sizeof(int*));

    for (int i = 0; i < num_vertices; i++) {

        g->matriz[i] = (int*) calloc(num_vertices, sizeof(int));
    }
    
    return g;
}

void adicionar_aresta(Grafo *g, int u, int v, int peso) {

    g->matriz[u][v] = peso;
    g->matriz[v][u] = peso;
}

void liberar_grafo(Grafo *g) {

    for (int i = 0; i < g->num_vertices; i++) free(g->matriz[i]);
    free(g->matriz);
    free(g);
}

Grafo* gerar_grafo_aleatorio(int num_vertices, double prob) {

    Grafo *g = criar_grafo(num_vertices);

    for (int i = 0; i < num_vertices; i++) {

        for (int j = i + 1; j < num_vertices; j++) {

            if ((rand() / (double)RAND_MAX) < prob) {

                adicionar_aresta(g, i, j, 1);
            }
        }
    }

    return g;
}

// Função auxiliar para backtracking
bool backtrack_hamiltoniano(Grafo *g, int *caminho, bool *visitado, int pos, bool procurar_ciclo) {

    if (pos == g->num_vertices) {

        if (!procurar_ciclo) return true;
        return g->matriz[caminho[pos - 1]][caminho[0]] != 0;
    }

    for (int v = 0; v < g->num_vertices; v++) {

        if (!visitado[v] && g->matriz[caminho[pos - 1]][v] != 0) {

            visitado[v] = true;
            caminho[pos] = v;

            if (backtrack_hamiltoniano(g, caminho, visitado, pos + 1, procurar_ciclo))
                return true;
            visitado[v] = false;
        }
    }

    return false;
}

bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho) {

    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));

    for (int i = 0; i < g->num_vertices; i++) {

        visitado[i] = true;
        caminho[0] = i;

        if (backtrack_hamiltoniano(g, caminho, visitado, 1, false)) {

            free(visitado);
            return true;
        }

        visitado[i] = false;
    }

    free(visitado);
    return false;
}

bool encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo) {

    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));
    visitado[0] = true;
    ciclo[0] = 0; 

    if (backtrack_hamiltoniano(g, ciclo, visitado, 1, true)) {

        free(visitado);
        return true;
    }

    free(visitado);
    return false;
}