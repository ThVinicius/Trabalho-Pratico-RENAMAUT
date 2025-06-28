#include "resetar-lista.service.h"

void limparListaRegistro(ListaRegistro **lista)
{
  ListaRegistro *atual = *lista;
  ListaRegistro *proximo;

  while (atual != NULL)
  {
    proximo = atual->next;
    free(atual);
    atual = proximo;
  }

  *lista = NULL;
}