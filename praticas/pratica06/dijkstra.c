#include "dijkstra.h"

// ================= FUNÇÕES DO GRAFO ================= //

GrafoListaPonderado* criar_grafo(int num_vertices){

    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->vetor_listas = (ListaAdj*) malloc(num_vertices * sizeof(ListaAdj));
    
    for (int i = 0; i < num_vertices; i++) {
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

    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->vetor_listas[i].cabeca;
        while (atual != NULL) {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->vetor_listas);
    free(g);
}

// ================= FUNÇÕES DO MIN-HEAP ================= //

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

    if (esquerda < heap->tamanho && heap->dados[esquerda].distancia < heap->dados[menor].distancia)
        menor = esquerda;

    if (direita < heap->tamanho && heap->dados[direita].distancia < heap->dados[menor].distancia)
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

int heap_vazio(MinHeap *heap) {

    return heap->tamanho == 0;
}

NoHeap extrair_minimo(MinHeap *heap){

    if (heap_vazio(heap)) {
        NoHeap no_vazio = {-1, -1};
        return no_vazio;
    }

    NoHeap raiz = heap->dados[0];
    NoHeap ultimo_no = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo_no;

    // Atualiza a posição do último nó e remove a raiz do mapa
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo_no.vertice] = 0;

    heap->tamanho--;
    min_heapify(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia){

    int i = heap->posicao[vertice];
    
    heap->dados[i].distancia = nova_distancia;

    while (i > 0 && heap->dados[i].distancia < heap->dados[(i - 1) / 2].distancia){
    
        heap->posicao[heap->dados[i].vertice] = (i - 1) / 2;
        heap->posicao[heap->dados[(i - 1) / 2].vertice] = i;

        trocar_no_heap(&heap->dados[i], &heap->dados[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void liberar_min_heap(MinHeap *heap) {

    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

// ================= FUNÇÕES DO ALGORITMO ================= //

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    int V = g->num_vertices;
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        pred[v] = -1;
        heap->dados[v].vertice = v;
        heap->dados[v].distancia = dist[v];
        heap->posicao[v] = v;
    }

    dist[origem] = 0;
    heap->dados[origem].distancia = 0;
    diminuir_chave(heap, origem, dist[origem]);
    heap->tamanho = V;

    while (!heap_vazio(heap)){

        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        Aresta *atual = g->vetor_listas[u].cabeca;
        while (atual != NULL){
            int v = atual->destino;
            
            if (heap->posicao[v] != -1 && dist[u] != INT_MAX && dist[u] + atual->peso < dist[v]){
                dist[v] = dist[u] + atual->peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            atual = atual->prox;
        }
    }
    liberar_min_heap(heap);
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