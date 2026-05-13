#include <stdlib.h>
#include "codigo.h"
#include "lista.h"

boolean novo_codigo (Codigo* c /* por referência */)
{
    c->byte=(U8*)malloc(1*sizeof(U8));
    if (c->byte==NULL) return false;

    c->capacidade=8;
    c->tamanho=0;
    return true;
}

void free_codigo (Codigo* c /* por referência */)
{
    if (c->byte!=NULL) free(c->byte);
    c->byte=NULL;
}

boolean adiciona_bit (Codigo* c, U8 valor)
{

    if (c->tamanho == c->capacidade)
    {
        U64 novos_bytes = (c->capacidade / 8) + 1;
        U8* novo = (U8*)realloc(c->byte, novos_bytes * sizeof(U8));
        if (novo == NULL) return false;

        c->byte = novo;
        c->byte[novos_bytes - 1] = 0; 
        c->capacidade += 8;
    }

    if (valor == 1) {
        int indice_byte = c->tamanho / 8;
        int posicao_bit = 7 - (c->tamanho % 8);
        c->byte[indice_byte] |= (1 << posicao_bit);
    }

    c->tamanho++;
    return true;
}


boolean joga_fora_bit (Codigo* c) {
    if (c == NULL || c->tamanho == 0) return false;
    
    c->tamanho--;
    
    c->byte[c->tamanho / 8] &= ~(1 << (7 - (c->tamanho % 8)));
    
    return true;
}

boolean pega_byte (Codigo c /* por valor "*/,
                   U8 qual /* por valor */,
                   U8* b /*por referencia */)
{
	if (qual>c.capacidade/8) return false;
	
	*b = c.byte[qual];
	return true;
}

boolean clone(Codigo original, Codigo* copia) {
    if (copia == NULL) return false;
    
    if (copia->byte != NULL) free(copia->byte);

    U64 num_bytes = (original.capacidade / 8);
    if (num_bytes == 0) num_bytes = 1; 

    copia->byte = (U8*)malloc(num_bytes * sizeof(U8));
    if (copia->byte == NULL) return false;

    for (U64 i = 0; i < num_bytes; i++) {
        copia->byte[i] = original.byte[i];
    }

    copia->capacidade = original.capacidade;
    copia->tamanho = original.tamanho;
    return true;
}

char* toString (Codigo c)
{
    char* retorno = (char*)malloc((c.tamanho + 1) * sizeof(char));
    if (retorno == NULL) return NULL;

    for (U64 i = 0; i < c.tamanho; i++) {
        U8 byte_atual = c.byte[i / 8];
        U8 bit = (byte_atual >> (7 - (i % 8))) & 1;
        retorno[i] = bit ? '1' : '0';
    }
    retorno[c.tamanho] = '\0';
    return retorno;
}
