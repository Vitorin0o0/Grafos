#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    int n = 4;
    
    // MATRIZ
    GrafoMatriz gm;
    criar_grafo_matriz(&gm, n);
    
    inserir_aresta_matriz(&gm, 0, 1);
    inserir_aresta_matriz(&gm, 0, 2);
    
    printf("[Matriz] Grau do vertice 0: %d\n", grau_matriz(&gm, 0));
    printf("[Matriz] 0 e 1 adjacentes? ");
    sao_adjacentes_matriz(&gm, 0, 1);
    
    remover_aresta_matriz(&gm, 0, 1);
    printf("[Matriz] 0 e 1 adjacentes apos remocao? ");
    sao_adjacentes_matriz(&gm, 0, 1);
    
    liberar_grafo_matriz(&gm);

    //LISTA
    GrafoLista gl;
    criar_grafo_lista(&gl, n);
    
    inserir_aresta_lista(&gl, 0, 1);
    inserir_aresta_lista(&gl, 0, 2);

    printf("[Lista] Grau do vertice 0: %d\n", grau_lista(&gl, 0));
    printf("[Lista] 0 e 1 adjacentes? ");
    sao_adjacentes_lista(&gl, 0, 1);

    remover_aresta_lista(&gl, 0, 1);
    printf("[Lista] 0 e 1 adjacentes apos remocao? ");
    sao_adjacentes_lista(&gl, 0, 1);
    
    liberar_grafo_lista(&gl);

    return 0;
}