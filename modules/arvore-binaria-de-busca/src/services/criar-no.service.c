#include "./criar-no.service.h"

NoABB *criarNo(Registro maquina)
{
  NoABB *novoNo = (NoABB *)malloc(sizeof(NoABB));

  if (novoNo == NULL)
  {
    return NULL;
  }

  novoNo->dados = maquina;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;

  return novoNo;
}