#include "./resetar-arvore.service.h"

void limparArvore(NoABB **raiz)
{
  if (*raiz != NULL)
  {
    /*Libera a subárvore esquerda*/
    limparArvore(&((*raiz)->esquerda));

    /*Libera a subárvore direita*/
    limparArvore(&((*raiz)->direita));

    /*Libera o próprio nó*/
    free(*raiz);
    *raiz = NULL;
  }
}