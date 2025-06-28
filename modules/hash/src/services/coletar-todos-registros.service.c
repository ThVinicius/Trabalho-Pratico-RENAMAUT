#include "coletar-todos-registros.service.h"

void coletar_todos_registros_hash(TabelaHash *tabela, GerenciadorListaRegistro *gerenciador_ref)
{
  int i;
  if (tabela == NULL)
  {
    return;
  }

  for (i = 0; i < TAMANHO_TABELA_HASH; i++)
  {
    /* Cada balde é um GerenciadorListaRegistro */
    if (tabela->baldes[i] != NULL && tabela->baldes[i]->head != NULL)
    {
      ListaRegistro *atual_no_balde = tabela->baldes[i]->head;
      while (atual_no_balde != NULL)
      {
        adicionar_registro_na_lista(gerenciador_ref, atual_no_balde->registro);
        atual_no_balde = atual_no_balde->next;
      }
    }
  }
}