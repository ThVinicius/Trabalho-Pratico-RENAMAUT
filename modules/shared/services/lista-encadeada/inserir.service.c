#include "inserir.service.h"
#include <stdio.h>

void *inserir_na_lista_encadeada_ordenada(EstruturaDados estrutura_dados, Registro maquina)
{
  ListaRegistro *cabeca = (ListaRegistro *)estrutura_dados;
  ListaRegistro *novo_no;
  ListaRegistro *atual;
  int comparacao;

  novo_no = criar_no_lista_registro_simples(maquina);
  if (novo_no == NULL)
  {
    return cabeca;
  }

  /* Caso 1: A lista está vazia */
  if (cabeca == NULL)
  {
    return (void *)novo_no;
  }

  /* Caso 2: Novo nó deve ser o primeiro ou é uma duplicata do primeiro */
  comparacao = strcmp(novo_no->registro.renamaut, cabeca->registro.renamaut);
  if (comparacao < 0)
  {
    /* Novo nó é menor que a cabeça, insere no início */
    novo_no->next = cabeca;
    return (void *)novo_no;
  }
  else if (comparacao == 0)
  {
    /* Duplicata do primeiro nó */
    printf("Aviso: Máquina com registro %s já existe. Ignorando inserção (cabeça).\n", maquina.renamaut);
    free(novo_no); /* Libera o nó duplicado */
    return cabeca;
  }

  /* Caso 3: Encontrar a posição correta para inserir ou identificar duplicata no meio/fim */
  atual = cabeca;

  while (atual->next != NULL && strcmp(novo_no->registro.renamaut, atual->next->registro.renamaut) > 0)
  {
    atual = atual->next;
  }

  /* Verifica se o próximo nó é uma duplicata */
  if (atual->next != NULL && strcmp(novo_no->registro.renamaut, atual->next->registro.renamaut) == 0)
  {
    printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
    free(novo_no); /* Libera o nó duplicado */
    return cabeca;
  }
  else
  {
    /* Insere o novo nó na posição correta */
    novo_no->next = atual->next;
    atual->next = novo_no;
  }

  return (void *)cabeca;
}