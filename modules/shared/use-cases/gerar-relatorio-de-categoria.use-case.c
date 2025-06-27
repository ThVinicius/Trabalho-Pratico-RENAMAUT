#include "gerar-relatorio-de-categoria.use-case.h"
#include "../services/relatorio-por-categoria/gerenciador-lista-estado.service.h"
#include "../services/relatorio-por-categoria/imprimir-relatorio-categoria.service.h"
#include "../services/adicionar-registro-na-lista.service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gerar_relatorio_de_categoria(EstruturaDados estrutura_dados, const char *categoria_cod, ColetarMaquinasPorCategoriaEEstadoCallback coletar_fn)
{
  GerenciadorListaEstados *gerenciador_estados = inicializarGerenciadorListaEstados();
  if (gerenciador_estados == NULL)
  {
    return;
  }

  coletar_fn(estrutura_dados, categoria_cod, gerenciador_estados);

  imprimirRelatorioCategoria(gerenciador_estados, categoria_cod);

  liberarGerenciadorListaEstados(gerenciador_estados);
  free(gerenciador_estados);
}