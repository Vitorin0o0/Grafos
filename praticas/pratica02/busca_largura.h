#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct {
    int num_vertices;
    No** listas_adj;
} GrafoLista;

typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;

Fila* criar_fila(int capacidade);
void destruir_fila(Fila *f);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);

#endif