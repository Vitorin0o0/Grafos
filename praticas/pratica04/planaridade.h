#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"

int eh_planar_euler(GrafoLista *g);
int possui_subdivisao_k5_ou_k33(GrafoLista *g);
int verificar_planaridade(GrafoLista *g);

#endif