#include "bellman_ford.h"

// ================= FUNÇÕES DO GRAFO ================= //

GrafoListaPonderado* criar_grafo(int num_vertices){

    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->vetor_listas = (ListaAdj*) malloc(num_vertices * sizeof(ListaAdj));
    
    for (int i = 0; i < num_vertices; i++){

        g->vetor_listas[i].cabeca = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso){

    Aresta *nova_aresta = (Aresta*) malloc(sizeof(Aresta));
    nova_aresta->destino = destino;
    nova_aresta->peso = peso;
    nova_aresta->prox = g->vetor_listas[origem].cabeca;
    g->vetor_listas[origem].cabeca = nova_aresta;
}

void liberar_grafo(GrafoListaPonderado *g){

    for (int i = 0; i < g->num_vertices; i++){

        Aresta *atual = g->vetor_listas[i].cabeca;
        while (atual != NULL){

            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    
    free(g->vetor_listas);
    free(g);
}

// ================= FUNÇÕES DO ALGORITMO ================= //

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred, int *vertice_ciclo){

    int V = g->num_vertices;

    for (int v = 0; v < V; v++){

        dist[v] = INT_MAX;
        pred[v] = -1;
    }
    dist[origem] = 0;

    for (int i = 1; i < V; i++){

        for (int u = 0; u < V; u++){

            Aresta *atual = g->vetor_listas[u].cabeca;

            while (atual != NULL){

                int v = atual->destino;
                int peso = atual->peso;
                if (dist[u] != INT_MAX && dist[u] + peso < dist[v]){

                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }

                atual = atual->prox;
            }
        }
    }

    
    for (int u = 0; u < V; u++){

        Aresta *atual = g->vetor_listas[u].cabeca;
        while (atual != NULL){

            int v = atual->destino;
            int peso = atual->peso;
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                *vertice_ciclo = v; 
                return 0; 
            }
            atual = atual->prox;
        }
    }

    return 1; 
}

void reconstruir_ciclo_negativo(int vertice_ciclo, int *pred, int num_vertices){

    int *ciclo = (int *) malloc(num_vertices * sizeof(int));
    int atual = vertice_ciclo;

    for (int i = 0; i < num_vertices; i++) {
        atual = pred[atual];
    }

    int inicio_ciclo = atual;
    int count = 0;

    do {
        ciclo[count++] = atual;
        atual = pred[atual];
    } while (atual != inicio_ciclo && count < num_vertices);

    ciclo[count++] = inicio_ciclo; 

    printf("Ciclo negativo detectado: ");
    
    for (int i = count - 1; i >= 0; i--){

        printf("%d ", ciclo[i]);
        if (i > 0) printf("-> ");
    }
    printf("\n");

    free(ciclo);
}

void reconstruir_caminho(int origem, int destino, int *pred){

    if (origem == destino) {
        printf("%d ", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Nao ha caminho de %d para %d.", origem, destino);
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf("-> %d ", destino);
}