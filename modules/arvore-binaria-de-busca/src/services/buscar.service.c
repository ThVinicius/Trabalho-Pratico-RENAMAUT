#include "./buscar.service.h"

Registro *buscar(EstruturaDados estrutura_dados, const char *numero_registro)
{
  NoABB *raiz = (NoABB *)estrutura_dados;
  int comparacao;

  if (raiz == NULL || strcmp(raiz->dados.renamaut, numero_registro) == 0)
  {
    return raiz ? &(raiz->dados) : NULL;
  }

  comparacao = strcmp(numero_registro, raiz->dados.renamaut);

  if (comparacao < 0)
  {
    return buscar((EstruturaDados)raiz->esquerda, numero_registro);
  }

  return buscar((EstruturaDados)raiz->direita, numero_registro);
}