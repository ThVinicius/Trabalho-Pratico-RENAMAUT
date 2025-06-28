#include "coletar-maquinas-por-responsavel-e-status.service.h"
#include <string.h>

static void _coletar_maquinas_por_responsavel_e_status_lista(ListaRegistro *lista_head, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  ListaRegistro *atual = lista_head;

  while (atual != NULL)
  {
    if (strcmp(atual->registro.resp, cpf_cnpj) == 0)
    {
      if (atual->registro.status == ATIVO)
      {
        adicionar_registro_na_lista(ativas_gerenciador, atual->registro);
      }
      else
      {
        adicionar_registro_na_lista(inativas_gerenciador, atual->registro);
      }
    }
    atual = atual->next;
  }
}

void coletar_maquinas_por_responsavel_e_status_hash(EstruturaDados estrutura_dados, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
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
      _coletar_maquinas_por_responsavel_e_status_lista(tabela->baldes[i]->head, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
    }
  }
}