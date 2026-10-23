#include "tps.h"
#include <stdlib.h>
#include <limits.h>

Grafo* grafo_para_tsp(Grafo *g) {

    Grafo *tsp_g = criar_grafo(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {

        for (int j = i + 1; j < g->num_vertices; j++) {

            int peso = (g->matriz[i][j] != 0) ? 1 : 2;
            adicionar_aresta(tsp_g, i, j, peso);
        }
    }
    
    return tsp_g;
}

void permutar_tsp(Grafo *g, int *caminho, bool *visitado, int pos, int custo_atual, int origem, int *melhor_custo, int *melhor_caminho) {
    
    if (pos == g->num_vertices) {

        int custo_final = custo_atual + g->matriz[caminho[pos - 1]][origem];

        if (custo_final < *melhor_custo) {

            *melhor_custo = custo_final;
            for (int i = 0; i < g->num_vertices; i++) melhor_caminho[i] = caminho[i];
        }
        return;
    }

    for (int v = 0; v < g->num_vertices; v++) {

        if (!visitado[v]) {
            visitado[v] = true;
            caminho[pos] = v;
            permutar_tsp(g, caminho, visitado, pos + 1, custo_atual + g->matriz[caminho[pos - 1]][v], origem, melhor_custo, melhor_caminho);
            visitado[v] = false;
        }
    }
}

int tsp_forca_bruta(Grafo *g, int origem, int *melhor_caminho) {

    int *caminho = (int*) malloc(g->num_vertices * sizeof(int));
    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));
    
    int melhor_custo = INT_MAX;
    visitado[origem] = true;
    caminho[0] = origem;

    permutar_tsp(g, caminho, visitado, 1, 0, origem, &melhor_custo, melhor_caminho);

    free(caminho);
    free(visitado);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(Grafo *g, int origem, int *caminho) {

    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));
    int atual = origem;
    int custo_total = 0;
    
    visitado[origem] = true;
    caminho[0] = origem;

    for (int i = 1; i < g->num_vertices; i++) {

        int proximo = -1;
        int menor_dist = INT_MAX;

        for (int v = 0; v < g->num_vertices; v++) {

            if (!visitado[v] && g->matriz[atual][v] < menor_dist) {

                menor_dist = g->matriz[atual][v];
                proximo = v;
            }
        }

        visitado[proximo] = true;
        caminho[i] = proximo;
        custo_total += menor_dist;
        atual = proximo;
    }

    custo_total += g->matriz[atual][origem]; 
    free(visitado);
    return custo_total;
}

int tsp_insercao(Grafo *g, int origem, int *caminho) {
    
    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));
    int num_inseridos = 0;
    
    caminho[0] = origem;
    visitado[origem] = true;
    num_inseridos++;
    
    while (num_inseridos < g->num_vertices) {

        int melhor_v = -1, melhor_pos = -1;
        int menor_aumento = INT_MAX;

        for (int v = 0; v < g->num_vertices; v++) {
            if (visitado[v]) continue;

            for (int i = 0; i < num_inseridos; i++) {

                int u1 = caminho[i];
                int u2 = caminho[(i + 1) % num_inseridos];
                int aumento = g->matriz[u1][v] + g->matriz[v][u2] - g->matriz[u1][u2];
                
                if (aumento < menor_aumento) {

                    menor_aumento = aumento;
                    melhor_v = v;
                    melhor_pos = i + 1;
                }
            }
        }
        
        for (int i = num_inseridos; i > melhor_pos; i--) {

            caminho[i] = caminho[i - 1];
        }

        caminho[melhor_pos] = melhor_v;
        visitado[melhor_v] = true;
        num_inseridos++;
    }

    int custo_total = 0;

    for (int i = 0; i < g->num_vertices; i++) {

        custo_total += g->matriz[caminho[i]][caminho[(i + 1) % g->num_vertices]];
    }

    free(visitado);
    return custo_total;
}