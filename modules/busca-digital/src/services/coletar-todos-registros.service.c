#include "coletar-todos-registros.service.h"
#include "../types/no-trie.type.h"

void coletar_todos_registros_trie(NoTrie *raiz, GerenciadorListaRegistro *gerenciador_ref)
{
  int i;
  if (raiz == NULL)
  {
    return;
  }

  if (raiz->is_end_of_key)
  {
    adicionar_registro_na_lista(gerenciador_ref, raiz->dados);
  }

  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    if (raiz->children[i] != NULL)
    {
      coletar_todos_registros_trie(raiz->children[i], gerenciador_ref);
    }
  }
}