#include "resetar-hash.service.h"
#include <stdio.h>

void limparTabelaHash(TabelaHash *tabela)
{
  int i;

  if (tabela == NULL)
  {
    return;
  }

  for (i = 0; i < TAMANHO_TABELA_HASH; i++)
  {
    if (tabela->baldes[i] != NULL)
    {
      limparArvoreAVL(&(tabela->baldes[i]));
    }
  }

  free(tabela);
}