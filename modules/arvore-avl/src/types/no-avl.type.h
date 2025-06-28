#ifndef NO_AVL_TYPE_H
#define NO_AVL_TYPE_H

#include "../../../shared/types/registro.type.h"

typedef struct NoAVL
{
  Registro dados;
  struct NoAVL *esquerda;
  struct NoAVL *direita;
  int altura;
} NoAVL;

#endif