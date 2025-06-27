#include "inicializar-gerenciador-lista-estados.service.h"

NoEstadoRelatorioCategoria *criarNoEstadoRelatorioCategoria(const char *uf)
{
  NoEstadoRelatorioCategoria *novoNo = (NoEstadoRelatorioCategoria *)malloc(sizeof(NoEstadoRelatorioCategoria));
  if (novoNo == NULL)
  {
    return NULL;
  }

  strncpy(novoNo->uf, uf, sizeof(novoNo->uf) - 1);
  novoNo->uf[sizeof(novoNo->uf) - 1] = '\0';
  novoNo->maquinas_no_estado = inicializarGerenciadorLista();
  novoNo->prox = NULL;
  return novoNo;
}
