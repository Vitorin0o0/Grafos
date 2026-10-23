#include "agm.h"

// ================= DSU (UNION-FIND) ================= //

DSU* criar_dsu(int n) {
    DSU *d = (DSU*) malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*) malloc(n * sizeof(int));
    d->rank = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
        d->rank[i] = 0;
    }
    return d;
}

// Busca com compressão de caminho
int find(DSU *d, int x){

    if (d->pai[x] != x){

        d->pai[x] = find(d, d->pai[x]); 
    }
    
    return d->pai[x];
}

// União por rank
void unir(DSU *d, int x, int y) {
    int raizX = find(d, x);
    int raizY = find(d, y);

    if (raizX != raizY) {
        if (d->rank[raizX] < d->rank[raizY]){
            d->pai[raizX] = raizY;
        } else if (d->rank[raizX] > d->rank[raizY]){
            d->pai[raizY] = raizX;
        } else{
            d->pai[raizY] = raizX;
            d->rank[raizX]++;
        }
    }
}

void liberar_dsu(DSU *d){

    free(d->pai);
    free(d->rank);
    free(d);
}

// ================= GRAFO E ARESTAS ================= //

GrafoLista* criar_grafo(int num_vertices){

    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->vetor_listas = (ListaAdj*) malloc(num_vertices * sizeof(ListaAdj));

    for (int i = 0; i < num_vertices; i++){

        g->vetor_listas[i].cabeca = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, Aresta *arestas, int *idx_aresta, int u, int v, int peso){
    
    NoAdj *novo1 = (NoAdj*) malloc(sizeof(NoAdj));
    novo1->destino = v;
    novo1->peso = peso;
    novo1->prox = g->vetor_listas[u].cabeca;
    g->vetor_listas[u].cabeca = novo1;

    NoAdj *novo2 = (NoAdj*) malloc(sizeof(NoAdj));
    novo2->destino = u;
    novo2->peso = peso;
    novo2->prox = g->vetor_listas[v].cabeca;
    g->vetor_listas[v].cabeca = novo2;

    if (arestas != NULL && idx_aresta != NULL){

        arestas[*idx_aresta].u = u;
        arestas[*idx_aresta].v = v;
        arestas[*idx_aresta].peso = peso;
        (*idx_aresta)++;
    }
}

void liberar_grafo(GrafoLista *g){

    for (int i = 0; i < g->num_vertices; i++){

        NoAdj *atual = g->vetor_listas[i].cabeca;

        while (atual != NULL){

            NoAdj *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->vetor_listas);
    free(g);
}

// ================= KRUSKAL ================= //

int comparar_arestas(const void *a, const void *b){

    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

void kruskal(Aresta *arestas, int E, int V){

    qsort(arestas, E, sizeof(Aresta), comparar_arestas);
    DSU *d = criar_dsu(V);
    int custo_total = 0;
    int arestas_selecionadas = 0;

    printf("Arestas na AGM (Kruskal):\n");
    for (int i = 0; i < E; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        if (find(d, u) != find(d, v)){

            unir(d, u, v);
            printf("%d -- %d == %d\n", u, v, peso);
            custo_total += peso;
            arestas_selecionadas++;
            if (arestas_selecionadas == V - 1) break;
        }
    }

    printf("Custo Total (Kruskal): %d\n", custo_total);
    liberar_dsu(d);
}

// ================= MIN-HEAP (PRIM) ================= //

MinHeap* criar_min_heap(int capacidade){

    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    return heap;
}

void trocar_no_heap(NoHeap *a, NoHeap *b){
    
    NoHeap temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap *heap, int idx){

    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < heap->tamanho && heap->dados[esquerda].chave < heap->dados[menor].chave)
        menor = esquerda;

    if (direita < heap->tamanho && heap->dados[direita].chave < heap->dados[menor].chave)
        menor = direita;

    if (menor != idx) {
        NoHeap menor_no = heap->dados[menor];
        NoHeap idx_no = heap->dados[idx];
        heap->posicao[menor_no.vertice] = idx;
        heap->posicao[idx_no.vertice] = menor;
        trocar_no_heap(&heap->dados[menor], &heap->dados[idx]);
        min_heapify(heap, menor);
    }
}

int heap_vazio(MinHeap *heap) { return heap->tamanho == 0; }

NoHeap extrair_minimo(MinHeap *heap){

    if (heap_vazio(heap)) return (NoHeap){-1, -1};
    NoHeap raiz = heap->dados[0];
    NoHeap ultimo_no = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo_no;
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo_no.vertice] = 0;
    heap->tamanho--;

    min_heapify(heap, 0);
    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_chave){

    int i = heap->posicao[vertice];
    heap->dados[i].chave = nova_chave;

    while (i > 0 && heap->dados[i].chave < heap->dados[(i - 1) / 2].chave){

        heap->posicao[heap->dados[i].vertice] = (i - 1) / 2;
        heap->posicao[heap->dados[(i - 1) / 2].vertice] = i;
        trocar_no_heap(&heap->dados[i], &heap->dados[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// ================= PRIM ================= //

void prim(GrafoLista *g, int origem){

    int V = g->num_vertices;
    int *pai = (int*) malloc(V * sizeof(int));
    int *chave = (int*) malloc(V * sizeof(int));
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++){

        pai[v] = -1;
        chave[v] = INT_MAX;
        heap->dados[v].vertice = v;
        heap->dados[v].chave = chave[v];
        heap->posicao[v] = v;
    }

    chave[origem] = 0;
    heap->dados[origem].chave = 0;
    diminuir_chave(heap, origem, chave[origem]);
    heap->tamanho = V;

    while (!heap_vazio(heap)){

        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        NoAdj *atual = g->vetor_listas[u].cabeca;

        while (atual != NULL){

            int v = atual->destino;

            if (heap->posicao[v] != -1 && atual->peso < chave[v]){

                chave[v] = atual->peso;
                pai[v] = u;
                diminuir_chave(heap, v, chave[v]);
            }

            atual = atual->prox;
        }
    }

    int custo_total = 0;
    printf("Arestas na AGM (Prim):\n");

    for (int i = 1; i < V; i++){

        if (pai[i] != -1){

            printf("%d -- %d == %d\n", pai[i], i, chave[i]);
            custo_total += chave[i];
        }
    }

    printf("Custo Total (Prim): %d\n", custo_total);

    free(pai);
    free(chave);
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}