#include <stdlib.h>
#include "./free-list.h"

void liberar_lista(Registros *cabeca_lista)
{
  Registros *atual = cabeca_lista;
  Registros *proximo;
  while (atual != NULL)
  {
    proximo = atual->next;
    free(atual);
    atual = proximo;
  }
}