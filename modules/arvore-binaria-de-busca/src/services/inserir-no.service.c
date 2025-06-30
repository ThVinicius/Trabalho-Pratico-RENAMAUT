#include "./inserir-no.service.h"
#include <stdio.h>
#include <string.h>

NoABB *inserir(NoABB *raiz, Registro maquina)
{
  NoABB *novoNo;
  NoABB *atual;
  NoABB *pai;
  int comparacao;

  /* Caso 1: Se a árvore está vazia, o novo nó se torna a raiz. */
  if (raiz == NULL)
  {
    return criarNo(maquina);
  }

  atual = raiz;
  pai = NULL;

  /* Percorre a árvore de forma iterativa para encontrar o local de inserção. */
  while (atual != NULL)
  {
    pai = atual; /* Atualiza o pai para o nó atual antes de avançar */
    comparacao = strcmp(maquina.renamaut, atual->dados.renamaut);

    if (comparacao < 0)
    {
      /* Se a nova máquina é "menor", vai para a subárvore esquerda. */
      atual = atual->esquerda;
    }
    else if (comparacao > 0)
    {
      /* Se a nova máquina é "maior", vai para a subárvore direita. */
      atual = atual->direita;
    }
    else
    {
      /* Caso de chave duplicada */
      printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
      return raiz;
    }
  }

  /* Se o loop terminou, 'atual' é NULL e 'pai' é o nó onde a nova máquina deve ser anexada. */

  novoNo = criarNo(maquina);
  if (novoNo == NULL)
  {
    return raiz;
  }

  /* Anexa o novo nó como filho do nó 'pai'. */
  /* Compara novamente para determinar se deve ser filho esquerdo ou direito. */
  comparacao = strcmp(maquina.renamaut, pai->dados.renamaut);
  if (comparacao < 0)
  {
    pai->esquerda = novoNo;
  }
  else
  {
    pai->direita = novoNo;
  }

  return raiz;
}