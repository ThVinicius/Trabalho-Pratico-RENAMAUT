#include "coletar-todos-registros.service.h"

void coletar_todos_registros_lista_original(ListaRegistro *lista_head, GerenciadorListaRegistro *gerenciador_ref)
{
  ListaRegistro *atual = lista_head;
  while (atual != NULL)
  {
    adicionar_registro_na_lista(gerenciador_ref, atual->registro);
    atual = atual->next;
  }
}