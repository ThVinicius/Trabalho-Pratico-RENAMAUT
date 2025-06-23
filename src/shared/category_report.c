#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../types/registro.type.h"
#include "./free-list.h"

static Registros *inserir_ordenado_por_uf_then_renamaut(Registros *cabeca, Registro registro_para_inserir)
{
  Registros *novo_no;
  Registros *atual;
  int comparacao_uf;
  int comparacao_renamaut;

  novo_no = (Registros *)malloc(sizeof(Registros));
  if (novo_no == NULL)
  {
    perror("Falha ao alocar memória para novo nó do relatório de categoria");
    return cabeca;
  }
  novo_no->registro = registro_para_inserir;
  novo_no->next = NULL;

  /* Caso 1: A lista está vazia ou o novo nó deve ser o primeiro */
  if (cabeca == NULL)
  {
    return novo_no;
  }

  comparacao_uf = strcmp(novo_no->registro.uf, cabeca->registro.uf);
  if (comparacao_uf < 0)
  { /* Novo UF vem antes do UF da cabeça */
    novo_no->next = cabeca;
    return novo_no;
  }
  else if (comparacao_uf == 0)
  { /* Mesma UF, comparar por RENAMAUT */
    comparacao_renamaut = strcmp(novo_no->registro.renamaut, cabeca->registro.renamaut);
    if (comparacao_renamaut < 0)
    {
      novo_no->next = cabeca;
      return novo_no;
    }
  }

  /* Caso 2: Encontrar a posição correta para inserir o novo nó */
  atual = cabeca;
  while (atual->next != NULL)
  {
    comparacao_uf = strcmp(novo_no->registro.uf, atual->next->registro.uf);
    if (comparacao_uf < 0)
    { /* Novo UF vem antes do UF do próximo */
      break;
    }
    else if (comparacao_uf == 0)
    { /* Mesma UF, comparar por RENAMAUT */
      comparacao_renamaut = strcmp(novo_no->registro.renamaut, atual->next->registro.renamaut);
      if (comparacao_renamaut < 0)
      {
        break;
      }
    }
    atual = atual->next;
  }
  novo_no->next = atual->next;
  atual->next = novo_no;

  return cabeca;
}

void gerar_relatorio_categoria(Registros *lista_principal, const char *codigo_categoria)
{
  Registros *lista_filtrada_ordenada = NULL;
  Registros *atual_principal = lista_principal;
  Registros *maquina_para_exibir;
  char uf_impressa_anterior[3];

  /* 1. Filtrar máquinas ativas da categoria e criar lista ordenada por UF, depois RENAMAUT */
  while (atual_principal != NULL)
  {
    if (atual_principal->registro.status == ATIVO &&
        strcmp(atual_principal->registro.cat, codigo_categoria) == 0)
    {
      lista_filtrada_ordenada = inserir_ordenado_por_uf_then_renamaut(lista_filtrada_ordenada, atual_principal->registro);
    }
    atual_principal = atual_principal->next;
  }

  printf("\n--- Relatório por Categoria: %s ---\n", codigo_categoria);

  if (lista_filtrada_ordenada == NULL)
  {
    printf("Nenhuma máquina ativa encontrada para a categoria '%s'.\n", codigo_categoria);
  }
  else
  {
    strcpy(uf_impressa_anterior, ""); /* Inicializa para garantir que o primeiro estado seja impresso */
    maquina_para_exibir = lista_filtrada_ordenada;

    while (maquina_para_exibir != NULL)
    {
      /* Se a UF da máquina atual é diferente da UF impressa anteriormente, imprime o novo cabeçalho de estado */
      if (strcmp(uf_impressa_anterior, maquina_para_exibir->registro.uf) != 0)
      {
        strcpy(uf_impressa_anterior, maquina_para_exibir->registro.uf);
        printf("\nEstado: %s\n", uf_impressa_anterior);
      }

      printf("%s;%s;%s;%d;ativo;%s %s\n",
             maquina_para_exibir->registro.renamaut,
             maquina_para_exibir->registro.resp,
             maquina_para_exibir->registro.mod,
             maquina_para_exibir->registro.ano,
             maquina_para_exibir->registro.cidade,
             maquina_para_exibir->registro.uf);

      maquina_para_exibir = maquina_para_exibir->next;
    }
  }

  printf("\n--- Fim do Relatório por Categoria ---\n");

  liberar_lista(lista_filtrada_ordenada);
}