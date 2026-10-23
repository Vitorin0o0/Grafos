#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

// Funções para TPS / TSP
Grafo* grafo_para_tsp(Grafo *g);
int tsp_forca_bruta(Grafo *g, int origem, int *melhor_caminho);
int tsp_vizinho_mais_proximo(Grafo *g, int origem, int *caminho);
int tsp_insercao(Grafo *g, int origem, int *caminho);

#endif 