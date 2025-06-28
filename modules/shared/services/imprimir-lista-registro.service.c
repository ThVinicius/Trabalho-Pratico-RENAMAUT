#include "imprimir-lista-registro.service.h"

void imprimir_lista_registro(ListaRegistro *lista)
{
  ListaRegistro *atual = lista;

  if (atual == NULL)
  {
    printf("Lista vazia.\n");
    return;
  }

  while (atual != NULL)
  {
    imprimir_maquina_formatada(atual->registro);
    atual = atual->next;
  }
}