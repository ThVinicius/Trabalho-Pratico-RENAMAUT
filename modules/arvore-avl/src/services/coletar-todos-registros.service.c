#include "coletar-todos-registros.service.h"

void coletar_todos_registros_avl(NoAVL *raiz, GerenciadorListaRegistro *gerenciador_ref)
{
  if (raiz == NULL)
  {
    return;
  }
  coletar_todos_registros_avl(raiz->esquerda, gerenciador_ref);
  adicionar_registro_na_lista(gerenciador_ref, raiz->dados);
  coletar_todos_registros_avl(raiz->direita, gerenciador_ref);
}