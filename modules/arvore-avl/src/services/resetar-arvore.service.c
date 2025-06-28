#include "resetar-arvore.service.h"

void limparArvoreAVL(NoAVL **raiz)
{
  if (*raiz != NULL)
  {
    limparArvoreAVL(&((*raiz)->esquerda));

    limparArvoreAVL(&((*raiz)->direita));

    free(*raiz);
    *raiz = NULL;
  }
}