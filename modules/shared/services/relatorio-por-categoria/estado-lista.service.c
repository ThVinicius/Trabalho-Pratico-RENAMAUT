#include "estado-lista.service.h"
#include "../adicionar-registro-na-lista.service.h"
#include "../liberar-gerenciador-lista.service.h"
#include "../imprimir-lista-registro.service.h"
#include "../imprimir-maquina-formatada.service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GerenciadorListaEstados *inicializarGerenciadorListaEstados()
{
  GerenciadorListaEstados *gerenciador = (GerenciadorListaEstados *)malloc(sizeof(GerenciadorListaEstados));
  if (gerenciador == NULL)
  {
    return NULL;
  }
  gerenciador->head = NULL;
  gerenciador->tail = NULL;
  return gerenciador;
}

NoEstadoRelatorioCategoria *criarNoEstadoRelatorioCategoria(const char *uf)
{
  NoEstadoRelatorioCategoria *novoNo = (NoEstadoRelatorioCategoria *)malloc(sizeof(NoEstadoRelatorioCategoria));
  if (novoNo == NULL)
  {
    return NULL;
  }
  strncpy(novoNo->uf, uf, sizeof(novoNo->uf) - 1);
  novoNo->uf[sizeof(novoNo->uf) - 1] = '\0';

  novoNo->maquinas_no_estado->head = NULL;
  novoNo->maquinas_no_estado->tail = NULL;
  novoNo->prox = NULL;
  return novoNo;
}

NoEstadoRelatorioCategoria *adicionarEstadoOrdenadoRelatorioCategoria(GerenciadorListaEstados *gerenciador_ref, const char *uf)
{
  NoEstadoRelatorioCategoria *novoNo, *atual, *anterior = NULL;

  atual = gerenciador_ref->head;
  while (atual != NULL)
  {
    if (strcmp(atual->uf, uf) == 0)
    {
      return atual;
    }
    atual = atual->prox;
  }

  novoNo = criarNoEstadoRelatorioCategoria(uf);
  if (novoNo == NULL)
  {
    return NULL;
  }

  atual = gerenciador_ref->head;
  while (atual != NULL && strcmp(uf, atual->uf) > 0)
  {
    anterior = atual;
    atual = atual->prox;
  }

  if (anterior == NULL)
  {
    novoNo->prox = gerenciador_ref->head;
    gerenciador_ref->head = novoNo;
  }
  else
  {
    novoNo->prox = atual;
    anterior->prox = novoNo;
  }

  if (novoNo->prox == NULL)
  {
    gerenciador_ref->tail = novoNo;
  }
  return novoNo;
}

void liberarGerenciadorListaEstados(GerenciadorListaEstados *gerenciador_ref)
{
  NoEstadoRelatorioCategoria *atual_estado;
  NoEstadoRelatorioCategoria *proximo_estado;

  if (gerenciador_ref == NULL)
    return;

  atual_estado = gerenciador_ref->head;

  while (atual_estado != NULL)
  {
    proximo_estado = atual_estado->prox;

    liberar_lista_registro(&(atual_estado->maquinas_no_estado));
    free(atual_estado);
    atual_estado = proximo_estado;
  }
  gerenciador_ref->head = NULL;
  gerenciador_ref->tail = NULL;
}

void imprimirRelatorioCategoria(GerenciadorListaEstados *gerenciador_estados, const char *categoria_cod)
{
  NoEstadoRelatorioCategoria *atual_estado = gerenciador_estados->head;

  printf("\n--- Relatório de Máquinas Ativas por Categoria: %s ---\n", categoria_cod);

  if (atual_estado == NULL)
  {
    printf("Nenhuma máquina ativa encontrada para esta categoria.\n");
  }
  else
  {
    while (atual_estado != NULL)
    {
      printf("\n*** Estado: %s ***\n", atual_estado->uf);
      imprimir_lista_registro(atual_estado->maquinas_no_estado);
      atual_estado = atual_estado->prox;
    }
  }
  printf("--- Fim do Relatório de Categoria ---\n");
}