#include "gerar-relatorio-de-categoria.use-case.h"
#include "../../../shared/services/relatorio-por-categoria/gerenciador-lista-estado.service.h"
#include "../../../shared/services/relatorio-por-categoria/imprimir-relatorio-categoria.service.h"
#include "../../../shared/services/adicionar-registro-na-lista.service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void coletar_maquinas_por_categoria_e_estado(NoABB *raiz, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  if (raiz == NULL)
  {

    return;
  }

  coletar_maquinas_por_categoria_e_estado(raiz->esquerda, categoria_cod, gerenciador_estados_ref);

  if (raiz->dados.status == ATIVO && strcmp(raiz->dados.cat, categoria_cod) == 0)
  {
    NoEstadoRelatorioCategoria *no_estado_atual;

    no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, raiz->dados.uf);

    if (no_estado_atual != NULL)
    {
      adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), raiz->dados);
    }
  }

  coletar_maquinas_por_categoria_e_estado(raiz->direita, categoria_cod, gerenciador_estados_ref);
}

void gerar_relatorio_de_categoria(NoABB *raiz, const char *categoria_cod)
{
  GerenciadorListaEstados *gerenciador_estados = inicializarGerenciadorListaEstados();
  if (gerenciador_estados == NULL)
  {
    return;
  }

  coletar_maquinas_por_categoria_e_estado(raiz, categoria_cod, gerenciador_estados);

  imprimirRelatorioCategoria(gerenciador_estados, categoria_cod);

  liberarGerenciadorListaEstados(gerenciador_estados);
  free(gerenciador_estados);
}