#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

No* criar_no(int v){

    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = NULL;
    return novo;
}

void adicionar_aresta(GrafoLista *g, int u, int v){

    No *novo = criar_no(v);
    novo->prox = g->listas_adj[u];
    g->listas_adj[u] = novo;

    novo = criar_no(u);
    novo->prox = g->listas_adj[v];
    g->listas_adj[v] = novo;
}

GrafoLista* criar_grafo(int n){

    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->listas_adj = (No**) malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) g->listas_adj[i] = NULL;
    return g;
}

void liberar_grafo(GrafoLista *g){

    for (int i = 0; i < g->num_vertices; i++){
        No *atual = g->listas_adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas_adj);
    free(g);
}

int main(){

    int num_vertices = 6;
    GrafoLista *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 4);
    adicionar_aresta(g, 3, 4); // Cria um ciclo (0-1-3-4-2-0)

    printf("=== PRÁTICA 02: BUSCA EM GRAFOS ===\n\n");

   
    int *dist = (int*) malloc(num_vertices * sizeof(int));
    int *pred = (int*) malloc(num_vertices * sizeof(int));
    
    bfs(g, 0, dist, pred);
    printf("1. Distâncias a partir do vértice 0 (BFS):\n");

    for (int i = 0; i < num_vertices; i++) {
        printf("   - Vértice %d: Distância = %d, Predecessor = %d\n", i, dist[i], pred[i]);
    }

    printf("\n2. Componentes Conexos: %d\n", contar_componentes(g));

    printf("3. O grafo possui ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Não");

    printf("4. O grafo é bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Não");

   
    free(dist);
    free(pred);
    liberar_grafo(g);

    return 0;
}