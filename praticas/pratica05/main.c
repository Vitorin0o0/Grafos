#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

void exibir_resultado(const char *nome, int *cores, int num_vertices, int num_cores) {

    printf("--- %s ---\n", nome);
    printf("Total de cores utilizadas: %d\n", num_cores);

    for (int i = 0; i < num_vertices; i++) {

        printf("Vértice %d -> Cor %d\n", i, cores[i]);
    }
    printf("\n");
}

int main() {
    
    int n = 5;
    GrafoLista *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 0);

    printf("=== PRÁTICA 05 - COLORACÃO DE GRAFOS ===\n\n");

    if (eh_bipartido(g)) {
        printf("O grafo é Bipartido (Número Cromático <= 2).\n\n");
    } else {
        printf("O grafo NÃO é Bipartido (Necessita de ao menos 3 cores).\n\n");
    }

    int num_cores_guloso = 0;
    int *cores_guloso = coloracao_gulosa(g, &num_cores_guloso);
    exibir_resultado("Coloração Gulosa", cores_guloso, n, num_cores_guloso);

    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(g, &num_cores_wp);
    exibir_resultado("Coloração Welsh-Powell", cores_wp, n, num_cores_wp);

    free(cores_guloso);
    free(cores_wp);
    liberar_grafo(g);

    return 0;
}