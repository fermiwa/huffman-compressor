#ifndef LISTA_H
#define LISTA_H
#include "arvore.h"

typedef struct elemento {
    No *no_arvore;
    struct elemento *prox;   // ponteiro aponta pro próximo da lista
} Elemento;

void inserir_prioridade(Elemento **topo, No *novo_no);
#endif