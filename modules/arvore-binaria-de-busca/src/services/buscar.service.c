#include "./buscar.service.h"

NoABB *buscar(NoABB *raiz, const char *numero_registro)
{
  int comparacao;

  if (raiz == NULL || strcmp(raiz->dados.renamaut, numero_registro) == 0)
  {
    return raiz;
  }

  comparacao = strcmp(numero_registro, raiz->dados.renamaut);

  if (comparacao < 0)
  {
    return buscar(raiz->esquerda, numero_registro);
  }

  return buscar(raiz->direita, numero_registro);
}