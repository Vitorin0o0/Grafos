#ifndef GRAFO_LISTA
#define GRAFO_LISTA

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    
    int num_vertices;
    No **lista; 
} GrafoLista;

GrafoLista*criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);

#endif