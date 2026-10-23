#include "cobertura.h"

// ================= FUNÇÕES DO GRAFO ================= //

Grafo* criar_grafo(int num_vertices){
    
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->matriz = (int**) malloc(num_vertices * sizeof(int*));

    for (int i = 0; i < num_vertices; i++){

        g->matriz[i] = (int*) calloc(num_vertices, sizeof(int));
    }

    return g;
}

void adicionar_aresta(Grafo *g, int u, int v){

    g->matriz[u][v] = 1;
    g->matriz[v][u] = 1;
}

void liberar_grafo(Grafo *g){
    
    for (int i = 0; i < g->num_vertices; i++){

        free(g->matriz[i]);
    }

    free(g->matriz);
    free(g);
}

// ================= VERIFICAÇÃO ================= //

bool eh_cobertura(Grafo *g, int *cobertura){

    for (int u = 0; u < g->num_vertices; u++){

        for (int v = u + 1; v < g->num_vertices; v++){

            if (g->matriz[u][v] == 1){ 

                if (cobertura[u] == 0 && cobertura[v] == 0){

                    return false; 
                }
            }
        }
    }
    return true;
}

// ================= FORÇA BRUTA COM BACKTRACKING ================= //

void resolver_bt(Grafo *g, int v, int *cobertura_atual, int tam_atual, int *melhor_cobertura, int *melhor_tam){

    if (tam_atual >= *melhor_tam) return;

    if (v == g->num_vertices){

        if (eh_cobertura(g, cobertura_atual)){

            *melhor_tam = tam_atual;

            for (int i = 0; i < g->num_vertices; i++){

                melhor_cobertura[i] = cobertura_atual[i];
            }
        }
        return;
    }

    cobertura_atual[v] = 1;
    resolver_bt(g, v + 1, cobertura_atual, tam_atual + 1, melhor_cobertura, melhor_tam);

    cobertura_atual[v] = 0;
    resolver_bt(g, v + 1, cobertura_atual, tam_atual, melhor_cobertura, melhor_tam);
}

int cobertura_minima_bt(Grafo *g, int *melhor_cobertura){

    int n = g->num_vertices;
    int *cobertura_atual = (int*) calloc(n, sizeof(int));
    int melhor_tam = INT_MAX;

    resolver_bt(g, 0, cobertura_atual, 0, melhor_cobertura, &melhor_tam);

    free(cobertura_atual);
    return melhor_tam;
}

// ================= HEURÍSTICA GULOSA ================= //

int cobertura_gulosa(Grafo *g, int *cobertura){

    int n = g->num_vertices;
    for (int i = 0; i < n; i++) cobertura[i] = 0;

    int **arestas_restantes = (int**) malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++){

        arestas_restantes[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arestas_restantes[i][j] = g->matriz[i][j];
    }

    int tam_cobertura = 0;

    while (true){

        int max_grau = -1;
        int vertice_escolhido = -1;

        for (int i = 0; i < n; i++) {
            if (cobertura[i]) continue;
            
            int grau_atual = 0;
            for (int j = 0; j < n; j++){

                if (arestas_restantes[i][j]) grau_atual++;
            }

            if (grau_atual > max_grau){

                max_grau = grau_atual;
                vertice_escolhido = i;
            }
        }

        if (max_grau <= 0) break;

        cobertura[vertice_escolhido] = 1;
        tam_cobertura++;

        for (int j = 0; j < n; j++) {
            arestas_restantes[vertice_escolhido][j] = 0;
            arestas_restantes[j][vertice_escolhido] = 0;
        }
    }

    for (int i = 0; i < n; i++) free(arestas_restantes[i]);
    free(arestas_restantes);

    return tam_cobertura;
}

Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade_aresta){

    Grafo *g = criar_grafo(num_vertices);

    for (int i = 0; i < num_vertices; i++){

        for (int j = i + 1; j < num_vertices; j++){

            if ((rand() / (double)RAND_MAX) < probabilidade_aresta){

                adicionar_aresta(g, i, j);
            }
        }
    }

    return g;
}