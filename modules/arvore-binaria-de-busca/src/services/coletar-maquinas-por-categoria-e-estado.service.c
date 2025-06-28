#include "coletar-maquinas-por-categoria-e-estado.service.h"
#include <string.h> 

#include "../../../shared/services/relatorio-por-categoria/gerenciador-lista-estado.service.h"
#include "../../../shared/services/adicionar-registro-na-lista.service.h" 

void coletar_maquinas_por_categoria_e_estado_bst(EstruturaDados estrutura_dados, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  NoABB *raiz = (NoABB *)estrutura_dados;

  if (raiz == NULL)
  {
    return;
  }

  coletar_maquinas_por_categoria_e_estado_bst((EstruturaDados)raiz->esquerda, categoria_cod, gerenciador_estados_ref);

  if (raiz->dados.status == ATIVO && strcmp(raiz->dados.cat, categoria_cod) == 0)
  {
    NoEstadoRelatorioCategoria *no_estado_atual;

    no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, raiz->dados.uf);

    if (no_estado_atual != NULL)
    {
      adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), raiz->dados);
    }
  }

  coletar_maquinas_por_categoria_e_estado_bst((EstruturaDados)raiz->direita, categoria_cod, gerenciador_estados_ref);
}