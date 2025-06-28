#ifndef NO_TYPE_H
#define NO_TYPE_H

#include "../../../shared/types/registro.type.h"

typedef struct NoABB {
    Registro dados;
    struct NoABB *esquerda;
    struct NoABB *direita;
} NoABB;

#endif