#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h" 

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

Pilha* criar_pilha(int capacidade);
void destruir_pilha(Pilha *p);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);

void dfs_recursiva_aux(GrafoLista *g, int u, int *visitado, int *pred);
void dfs_recursiva(GrafoLista *g, int origem, int *visitado, int *pred);
void dfs_iterativa(GrafoLista *g, int origem, int *visitado);

int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif