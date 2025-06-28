#include "resetar-arvore.service.h"
#include "criar-no.service.h"

void limparTrie(NoTrie **raiz)
{
  if (*raiz != NULL)
  {
    int i;
    /* Libera recursivamente todos os filhos */
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
      limparTrie(&((*raiz)->children[i]));
    }

    /* Libera o próprio nó */
    free(*raiz);
    *raiz = NULL;
  }
}