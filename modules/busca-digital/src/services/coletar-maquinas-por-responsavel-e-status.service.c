#include "coletar-maquinas-por-responsavel-e-status.service.h"
#include "../types/no-trie.type.h"

static void _coletar_maquinas_por_responsavel_e_status_trie_recursiva(NoTrie *no, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  int i;

  if (no == NULL)
  {
    return;
  }

  /* Se este nó marca o fim de uma chave, verifica o responsável e status */
  if (no->is_end_of_key)
  {
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
  }

  /* Percorre recursivamente todos os filhos */
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    _coletar_maquinas_por_responsavel_e_status_trie_recursiva(no->children[i], cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
  }
}

void coletar_maquinas_por_responsavel_e_status_trie(EstruturaDados estrutura_dados, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  NoTrie *raiz = (NoTrie *)estrutura_dados;
  _coletar_maquinas_por_responsavel_e_status_trie_recursiva(raiz, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
}