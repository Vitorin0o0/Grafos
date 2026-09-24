#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {

    printf("==================================================\n");
    printf("  PRÁTICA 04: DETECÇÃO DE ARTICULAÇÕES E PLANARIDADE\n");
    printf("==================================================\n\n");

    printf(">>> GRAFO 1 (Com ponte e articulação) <<<\n");
    GrafoLista *g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 1, 2);
    adicionar_aresta(g1, 2, 0);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 4);

    detectar_pontes_e_articulacoes(g1);
    verificar_planaridade(g1);
    liberar_grafo(g1);

    printf("\n--------------------------------------------------\n\n");

    printf(">>> GRAFO 2 (Completo K5) <<<\n");
    GrafoLista *g2 = criar_grafo(5);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            adicionar_aresta(g2, i, j);
        }
    }

    detectar_pontes_e_articulacoes(g2);
    verificar_planaridade(g2);
    liberar_grafo(g2);

    return 0;
}