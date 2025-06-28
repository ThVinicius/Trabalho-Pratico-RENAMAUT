#include "coletar-maquinas-por-responsavel-e-status.service.h"
#include <string.h>

static void _coletar_maquinas_por_responsavel_e_status_avl_recursiva(NoAVL *no, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  if (no == NULL)
  {
    return;
  }

  _coletar_maquinas_por_responsavel_e_status_avl_recursiva(no->esquerda, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);

  if (strcmp(no->dados.resp, cpf_cnpj) == 0)
  {
    if (no->dados.status == ATIVO)
    {
      adicionar_registro_na_lista(ativas_gerenciador, no->dados);
    }
    else
    {
      adicionar_registro_na_lista(inativas_gerenciador, no->dados);
    }
  }

  _coletar_maquinas_por_responsavel_e_status_avl_recursiva(no->direita, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
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
    if (tabela->baldes[i] != NULL)
    {
      _coletar_maquinas_por_responsavel_e_status_avl_recursiva(tabela->baldes[i], cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
    }
  }
}
