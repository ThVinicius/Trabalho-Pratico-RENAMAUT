#include "./inserir-no.service.h"

NoABB *inserir(NoABB **raiz, Registro maquina)
{
  int comparacao;

  if (*raiz == NULL)
  {
    printf("DEBUG: Criando novo no para %s\n", maquina.renamaut);
    *raiz = criarNo(maquina);
    return *raiz;
  }

  comparacao = strcmp(maquina.renamaut, (*raiz)->dados.renamaut);

  if (comparacao < 0)
  {
    (*raiz)->esquerda = inserir(&((*raiz)->esquerda), maquina);
  }
  else if (comparacao > 0)
  {
    (*raiz)->direita = inserir(&((*raiz)->direita), maquina);
  }
  else
  {
    printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
  }

  return *raiz;
}