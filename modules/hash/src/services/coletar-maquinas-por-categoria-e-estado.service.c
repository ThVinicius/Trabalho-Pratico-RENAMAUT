#include "coletar-maquinas-por-categoria-e-estado.service.h"
#include <string.h>

static void _coletar_maquinas_por_categoria_e_estado_avl_recursiva(NoAVL *no, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  if (no == NULL)
  {
    return;
  }

  _coletar_maquinas_por_categoria_e_estado_avl_recursiva(no->esquerda, categoria_cod, gerenciador_estados_ref);

  if (no->dados.status == ATIVO && strcmp(no->dados.cat, categoria_cod) == 0)
  {
    NoEstadoRelatorioCategoria *no_estado_atual;

    no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, no->dados.uf);

    if (no_estado_atual != NULL)
    {
      adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), no->dados);
    }
  }

  _coletar_maquinas_por_categoria_e_estado_avl_recursiva(no->direita, categoria_cod, gerenciador_estados_ref);
}

void coletar_maquinas_por_categoria_e_estado_hash(EstruturaDados estrutura_dados, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  int i;
  TabelaHash *tabela = (TabelaHash *)estrutura_dados;

  if (tabela == NULL)
  {
    return;
  }

  for (i = 0; i < TAMANHO_TABELA_HASH; i++)
  {
    if (tabela->baldes[i] != NULL)
    {
      _coletar_maquinas_por_categoria_e_estado_avl_recursiva(tabela->baldes[i], categoria_cod, gerenciador_estados_ref);
    }
  }
}
