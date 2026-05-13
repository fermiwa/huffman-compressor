#include <stdlib.h>
#include <stdio.h>
#include "meustiposonlinegdb.h"
#include "arvore.h"
#include "codigo.h"
#include "lista.h" 

No* remover_inicio(Elemento **topo);
void inserir_prioridade(Elemento **topo, No *novo_no);

// Função que cria o nó
No* criar_no(U8 c, U64 freq) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo) {
        novo->caractere = c;
        novo->frequencia = freq;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// função que monta a árvore
No* montar_arvore(Elemento **topo) {
    while ((*topo) != NULL && (*topo)->prox != NULL) {
        // remove pra pegar os 2 com menos frequencia
        No *esq = remover_inicio(topo);
        No *dir = remover_inicio(topo);

        // o pai vai ser caracter # e freq = soma
        No *pai = criar_no('#', esq->frequencia + dir->frequencia);
        pai->esq = esq;
        pai->dir = dir;

        inserir_prioridade(topo, pai);
    }
    return remover_inicio(topo);
}

// função pra percorrer a árvore
void gerar_dicionario(No *raiz, Codigo *dicionario, Codigo *caminho_atual) {
    if (raiz->esq == NULL && raiz->dir == NULL) {
        // salvar o caminho percorrido
        clone(*caminho_atual, &dicionario[raiz->caractere]);
        return;
    }

    if (raiz->esq != NULL) {
        adiciona_bit(caminho_atual, 0); 
        gerar_dicionario(raiz->esq, dicionario, caminho_atual); // recursão
        joga_fora_bit(caminho_atual); 
    }

    if (raiz->dir != NULL) {
        adiciona_bit(caminho_atual, 1); 
        gerar_dicionario(raiz->dir, dicionario, caminho_atual); // recursão
        joga_fora_bit(caminho_atual); 
    }

    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("Salvando caractere %d no dicionario...\n", raiz->caractere);
        clone(*caminho_atual, &dicionario[raiz->caractere]);
        return;
    }   
}