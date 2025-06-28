#include "coletar-todos-registros.service.h"

void coletar_todos_registros_bst(NoABB *raiz, GerenciadorListaRegistro *gerenciador_ref)
{
  if (raiz == NULL)
  {
    return;
  }
  coletar_todos_registros_bst(raiz->esquerda, gerenciador_ref);
  adicionar_registro_na_lista(gerenciador_ref, raiz->dados);
  coletar_todos_registros_bst(raiz->direita, gerenciador_ref);
}