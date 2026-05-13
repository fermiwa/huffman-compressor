#include <stdio.h>
#include <stdlib.h>
#include "meustiposonlinegdb.h"
#include "codigo.h"  
#include "arvore.h" 
#include "lista.h"

void contar_frequencias(char *nome, U64 *freq);
No* montar_arvore(Elemento **topo);
void gerar_dicionario(No *raiz, Codigo *dicionario, Codigo caminho_atual);
void compactar_arquivo(char *nomeEntrada, char *nomeSaida, Codigo *dicionario, U64 *freq);
No* remover_inicio(Elemento **topo);

int main() {
    U64 freq[256] = {0};

    // pega freq pra poder descompactar depois
    contar_frequencias("teste.txt", freq);

    Elemento *lista = NULL;

    // passa pelo dicionario inteiro e salva
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            No *n = criar_no((U8)i, freq[i]);
            inserir_prioridade(&lista, n);
        }
    }

    No *raiz = montar_arvore(&lista);

    // pra debug
    if (raiz == NULL) {
        printf("Erro: A árvore não pôde ser montada. O arquivo está vazio?\n");
        return 1;
    }

    // inicializa o dicionario e usa calloc pois zera os campos iniciais
    Codigo* dicionario = (Codigo*)calloc(256, sizeof(Codigo));

    for (int i = 0; i < 256; i++) {
        if (dicionario[i].byte != NULL && dicionario[i].tamanho > 0) {
            char *bits = toString(dicionario[i]);
            if (bits != NULL) {
                printf("Char: %c | Codigo: %s\n", i, bits);
                free(bits);
            }
        }
    }
    
    Codigo caminho_aux;
    novo_codigo(&caminho_aux);

    gerar_dicionario(raiz, dicionario, caminho_aux);

    printf("\n--- DICIONARIO DE HUFFMAN ---\n");
    for (int i = 0; i < 256; i++) {
        if (dicionario[i].tamanho > 0) {
            char *bits = toString(dicionario[i]);
            printf("Char: %c | Codigo: %s\n", i, bits);
            free(bits);
        }
    }

    // print de debug
    printf("\nCompactando arquivo...");
    compactar_arquivo("teste.txt", "compactado.huf", dicionario, freq);
    printf("\nConcluido! Arquivo 'compactado.huf' gerado.");

    free_codigo(&caminho_aux); 
    free(dicionario);

    return 0;
}

// --- IMPLEMENTAÇÃO DA COMPACTAÇÃO ---
void compactar_arquivo(char *nomeEntrada, char *nomeSaida, Codigo *dicionario, U64 *freq) {
    FILE *entrada = fopen(nomeEntrada, "rb");
    FILE *saida = fopen(nomeSaida, "wb"); 

    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos!\n");
        if (entrada) fclose(entrada);
        if (saida) fclose(saida);
        return;
    }

    // cabeçalho
    fwrite(freq, sizeof(U64), 256, saida);

    // total caracteres
    U64 total_caracteres = 0;
    for(int i = 0; i < 256; i++) total_caracteres += freq[i];
    fwrite(&total_caracteres, sizeof(U64), 1, saida);

    Codigo buffer_saida;
    novo_codigo(&buffer_saida);

    U8 c;
    while (fread(&c, sizeof(U8), 1, entrada)) {
        Codigo cod = dicionario[c];
        
        if (cod.byte != NULL && cod.tamanho > 0) {
            for (U64 i = 0; i < cod.tamanho; i++) {
                // pega o bit i do código do dicionário
                U8 bit = (cod.byte[i / 8] >> (7 - (i % 8))) & 1;
                adiciona_bit(&buffer_saida, bit);
            }
        }
    }

    // print de debug
    printf("Debug: Tamanho total de bits no buffer: %llu\n", buffer_saida.tamanho);

    char *res = toString(buffer_saida);

    // print de debug
    printf("Bits no buffer: %s\n", res);
    free(res);

    // Escreve os bits empacotados
    fwrite(buffer_saida.byte, sizeof(U8), (buffer_saida.tamanho + 7) / 8, saida);

    fclose(entrada);
    fclose(saida);
    free_codigo(&buffer_saida);
}

void contar_frequencias(char *nome, U64 *freq) {
    FILE *f = fopen(nome, "rb");
    if (!f) {
        printf("ERRO: O arquivo '%s' nao foi encontrado no diretorio atual!\n", nome);
        return;
    }
    U8 byte;
    int lidos = 0;
    while (fread(&byte, sizeof(U8), 1, f)) {
        freq[byte]++;
        lidos++;
    }
    printf("Debug: Li %d bytes do arquivo.\n", lidos);
    fclose(f);
}