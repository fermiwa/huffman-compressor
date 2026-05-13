#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

// menor Frequência = maior prioridade (inicio da fila)
void inserir_prioridade(Elemento **topo, No *novo_no) {
    // aloca memória para o novo elemento da lista
    Elemento *novo_elem = (Elemento*) malloc(sizeof(Elemento));
    if (novo_elem == NULL) return; 

    novo_elem->no_arvore = novo_no;
    novo_elem->prox = NULL;

    // lista vazia ou freq menor = vira topo
    if (*topo == NULL || novo_no->frequencia < (*topo)->no_arvore->frequencia) {
        novo_elem->prox = *topo;
        *topo = novo_elem;
    } 
    else {
        // percorre a lista para achar a posição correta
        Elemento *atual = *topo;
        while (atual->prox != NULL && atual->prox->no_arvore->frequencia <= novo_no->frequencia) {
            atual = atual->prox;
        }
        
        // Insere o elemento entre 'atual' e 'atual->prox'
        novo_elem->prox = atual->prox;
        atual->prox = novo_elem;
    }
}

No* remover_inicio(Elemento **topo) {
    if (*topo == NULL) return NULL;
    
    // pega o topo (menor freq)
    Elemento *aux = *topo;
    No *no_retorno = aux->no_arvore;
    
    *topo = aux->prox; // agora aponto pro 2o elemento
    free(aux);
    
    return no_retorno;
}