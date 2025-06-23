#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../types/registro.type.h"
#include "./free-list.h"

Registros *inserir_ordenado_por_renamaut(Registros *cabeca, Registro registro_para_inserir)
{
  Registros *novo_no; /* Declaração movida para o topo do bloco */
  Registros *atual;   /* Declaração movida para o topo do bloco */

  novo_no = (Registros *)malloc(sizeof(Registros));
  if (novo_no == NULL)
  {
    perror("Falha ao alocar memória para novo nó do relatório");
    return NULL;
  }
  novo_no->registro = registro_para_inserir; /* Copia os dados do registro */
  novo_no->next = NULL;

  /* Caso 1: A lista está vazia ou o novo nó deve ser o primeiro */
  if (cabeca == NULL || strcmp(novo_no->registro.renamaut, cabeca->registro.renamaut) < 0)
  {
    novo_no->next = cabeca;
    return novo_no; /* Nova cabeça da lista */
  }

  /* Caso 2: Encontrar a posição correta para inserir o novo nó */
  atual = cabeca;
  while (atual->next != NULL && strcmp(novo_no->registro.renamaut, atual->next->registro.renamaut) >= 0)
  {
    atual = atual->next;
  }
  novo_no->next = atual->next;
  atual->next = novo_no;

  return cabeca;
}

void exibir_lista_formatada_para_relatorio(Registros *cabeca_lista)
{
  Registros *atual = cabeca_lista;
  if (atual == NULL)
  {
    printf("Nenhuma máquina encontrada para os critérios informados nesta seção.\n");
    return;
  }
  while (atual != NULL)
  {
    printf("%s;%s;%s;%d;%s;%s %s\n",
           atual->registro.renamaut,
           atual->registro.resp,
           atual->registro.mod,
           atual->registro.ano,
           atual->registro.status == ATIVO ? "ativo" : "inativo",
           atual->registro.cidade,
           atual->registro.uf);
    atual = atual->next;
  }
}

void gerar_relatorio_responsabilidade(Registros *lista_principal, const char *cpf_cnpj_responsavel)
{
  Registros *lista_ativos_responsavel = NULL;
  Registros *lista_inativos_responsavel = NULL;
  Registros *atual = lista_principal;

  /* 1. Filtrar registros pelo CPF/CNPJ e popular as listas de ativos e inativos ordenadamente. */
  while (atual != NULL)
  {
    if (strcmp(atual->registro.resp, cpf_cnpj_responsavel) == 0)
    {
      if (atual->registro.status == ATIVO)
      {
        lista_ativos_responsavel = inserir_ordenado_por_renamaut(lista_ativos_responsavel, atual->registro);
      }
      else
      {
        lista_inativos_responsavel = inserir_ordenado_por_renamaut(lista_inativos_responsavel, atual->registro);
      }
    }
    atual = atual->next;
  }

  printf("\n--- Relatório de Responsabilidade para: %s ---\n", cpf_cnpj_responsavel);

  printf("\nMáquinas com status ATIVO (ordenadas por número de registro):\n");
  exibir_lista_formatada_para_relatorio(lista_ativos_responsavel);

  printf("\nMáquinas com status INATIVO (ordenadas por número de registro):\n");
  exibir_lista_formatada_para_relatorio(lista_inativos_responsavel);

  printf("\n--- Fim do Relatório de Responsabilidade ---\n");

  liberar_lista(lista_ativos_responsavel);
  liberar_lista(lista_inativos_responsavel);
}