#include "liberar-gerenciador-lista.service.h"

void liberar_lista_registro(GerenciadorListaRegistro **gerenciador_ref)
{
  ListaRegistro *atual = (*gerenciador_ref)->head;
  ListaRegistro *proximo;

  while (atual != NULL)
  {
    proximo = atual->next;
    free(atual);
    atual = proximo;
  }

  (*gerenciador_ref)->head = NULL;
  (*gerenciador_ref)->tail = NULL;
}