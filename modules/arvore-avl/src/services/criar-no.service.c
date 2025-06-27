#include "./criar-no.service.h"

NoAVL *criarNoAVL(Registro maquina)
{
  NoAVL *novoNo = (NoAVL *)malloc(sizeof(NoAVL));

  if (novoNo == NULL)
  {
    return NULL;
  }

  novoNo->dados = maquina;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  novoNo->altura = 1;

  return novoNo;
}