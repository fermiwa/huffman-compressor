#include <stdio.h>
#include <stdlib.h>
#include "meustiposonlinegdb.h"
#include "arvore.h"
#include "lista.h"

No* montar_arvore(Elemento **topo);

int main() {
    FILE *entrada = fopen("compactado.huf", "rb");
    FILE *saida = fopen("saida_final.txt", "w");

    // print de debug
    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos para descompactacao!\n");
        return 1;
    }

    // pega as freq (do cabeçalho)
    U64 freq_recuperada[256];
    fread(freq_recuperada, sizeof(U64), 256, entrada);

    // pega o total de caracteres
    U64 total_caracteres;
    fread(&total_caracteres, sizeof(U64), 1, entrada);

    // recconstruir a árvore
    Elemento *lista = NULL;
    for (int i = 0; i < 256; i++) {
        if (freq_recuperada[i] > 0) {
            No *n = criar_no((U8)i, freq_recuperada[i]);
            inserir_prioridade(&lista, n);
        }
    }
    No *raiz = montar_arvore(&lista);

    // descompacta pela árvore
    No *atual = raiz;
    U64 caracteres_escritos = 0;
    U8 byte;

    // print de debug
    printf("Descompactando...\n");

    // bytes restantes
    while (caracteres_escritos < total_caracteres && fread(&byte, sizeof(U8), 1, entrada)) {
        for (int i = 0; i < 8 && caracteres_escritos < total_caracteres; i++) {
            U8 bit = (byte >> (7 - i)) & 1;
            
            // print de debug
            printf("Lendo bit: %d | Indo para: %s\n", bit, bit == 0 ? "Esquerda" : "Direita");

            if (bit == 0) atual = atual->esq;
            else          atual = atual->dir;

            if (atual->esq == NULL && atual->dir == NULL) {
                fputc(atual->caractere, saida);
                caracteres_escritos++;
                atual = raiz; 
            }
        }
    }

    // print de debug
    printf("Concluido! O arquivo 'saida_final.txt' foi gerado.\n");

    fclose(entrada);
    fclose(saida);
    return 0;
}