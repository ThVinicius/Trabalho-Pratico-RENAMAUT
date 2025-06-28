#include "coletar-maquinas-por-categoria-e-estado.service.h"
#include <string.h>

void _coletar_maquinas_por_categoria_e_estado_lista(ListaRegistro *lista_head, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  ListaRegistro *atual = lista_head;

  if (atual == NULL)
  {
    return;
  }

  while (atual != NULL)
  {
    if (atual->registro.status == ATIVO && strcmp(atual->registro.cat, categoria_cod) == 0)
    {
      NoEstadoRelatorioCategoria *no_estado_atual;

      no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, atual->registro.uf);

      if (no_estado_atual != NULL)
      {
        adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), atual->registro);
      }
    }
    atual = atual->next;
  }
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
    if (tabela->baldes[i] != NULL && tabela->baldes[i]->head != NULL)
    {
      _coletar_maquinas_por_categoria_e_estado_lista(tabela->baldes[i]->head, categoria_cod, gerenciador_estados_ref);
    }
  }
}