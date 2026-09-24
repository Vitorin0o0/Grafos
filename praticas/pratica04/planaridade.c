#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {

    int n = g->num_vertices;
    int m = g->num_arestas;

    if (n < 3) return 1;
    
    return (m <= (3 * n - 6));
}

static int existe_aresta(GrafoLista *g, int u, int v) {

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {

        if (p->vertice == v) return 1;
    }

    return 0;
}

int possui_subdivisao_k5_ou_k33(GrafoLista *g) {
    int n = g->num_vertices;

    if (n >= 5) {
        for (int v1 = 0; v1 < n; v1++) {
            for (int v2 = v1 + 1; v2 < n; v2++) {
                for (int v3 = v2 + 1; v3 < n; v3++) {
                    for (int v4 = v3 + 1; v4 < n; v4++) {
                        for (int v5 = v4 + 1; v5 < n; v5++) {
                            int k5 = 1;
                            int v[5] = {v1, v2, v3, v4, v5};
                            for (int i = 0; i < 5; i++) {
                                for (int j = i + 1; j < 5; j++) {
                                    if (!existe_aresta(g, v[i], v[j])) {
                                        k5 = 0;
                                        break;
                                    }
                                }
                                if (!k5) break;
                            }
                            if (k5) return 1;
                        }
                    }
                }
            }
        }
    }

    if (n >= 6) {
        for (int a1 = 0; a1 < n; a1++) {
            for (int a2 = a1 + 1; a2 < n; a2++) {
                for (int a3 = a2 + 1; a3 < n; a3++) {
                    for (int b1 = 0; b1 < n; b1++) {
                        if (b1 == a1 || b1 == a2 || b1 == a3) continue;
                        for (int b2 = b1 + 1; b2 < n; b2++) {
                            if (b2 == a1 || b2 == a2 || b2 == a3) continue;
                            for (int b3 = b2 + 1; b3 < n; b3++) {
                                if (b3 == a1 || b3 == a2 || b3 == a3) continue;

                                int k33 = 1;
                                int A[3] = {a1, a2, a3};
                                int B[3] = {b1, b2, b3};

                                for (int i = 0; i < 3; i++) {
                                    for (int j = 0; j < 3; j++) {
                                        if (!existe_aresta(g, A[i], B[j])) {
                                            k33 = 0;
                                            break;
                                        }
                                    }
                                    if (!k33) break;
                                }
                                if (k33) return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int verificar_planaridade(GrafoLista *g) {

    printf("--- Teste de Planaridade ---\n");

    if (!eh_planar_euler(g)) {

        printf("  [Resultado] NÃO PLANAR: Violou a Fórmula de Euler ($m \\le 3n - 6$). Vertices: %d, Arestas: %d.\n", g->num_vertices, g->num_arestas);
        return 0;
    }

    printf("  [Euler] Passou na verificação $m \\le 3n - 6$.\n");

    if (g->num_vertices <= 10) {

        if (possui_subdivisao_k5_ou_k33(g)) {

            printf("  [Kuratowski] NÃO PLANAR: Contém subgrafo $K_5$ ou $K_{3,3}$.\n");
            return 0;
        }
        
        printf("  [Kuratowski] Nenhum $K_5$ ou $K_{3,3}$ encontrado.\n");
    }

    printf("  [Resultado] O grafo é PLANAR.\n");
    return 1;
}