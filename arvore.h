#ifndef ARVORE_H
#define ARVORE_H
#include "meustiposonlinegdb.h"

typedef struct no {
    U8 caractere; 
    U64 frequencia;
    struct no *esq, *dir;
} No;

No* criar_no(U8 c, U64 freq);

#endif