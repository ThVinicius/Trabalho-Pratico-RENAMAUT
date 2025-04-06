#include <stdlib.h>
#include "resetar.h"

void resetar_lista(Registros **lista)
{
  Registros *atual = *lista;
  Registros *proximo;

  while (atual != NULL)
  {
    proximo = atual->next;
    free(atual);
    atual = proximo;
  }

  *lista = NULL;
}