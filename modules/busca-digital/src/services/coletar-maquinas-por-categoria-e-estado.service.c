#include "coletar-maquinas-por-categoria-e-estado.service.h"
#include "../types/no-trie.type.h"

/* Função auxiliar recursiva para percorrer a Trie */
static void _coletar_maquinas_por_categoria_e_estado_trie_recursiva(NoTrie *no, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  int i;

  if (no == NULL)
  {
    return;
  }

  /* Se este nó marca o fim de uma chave, verifica categoria e status */
  if (no->is_end_of_key)
  {
    if (no->dados.status == ATIVO && strcmp(no->dados.cat, categoria_cod) == 0)
    {
      NoEstadoRelatorioCategoria *no_estado_atual;
      no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, no->dados.uf);

      if (no_estado_atual != NULL)
      {
        adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), no->dados);
      }
    }
  }

  /* Percorre recursivamente todos os filhos */
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    _coletar_maquinas_por_categoria_e_estado_trie_recursiva(no->children[i], categoria_cod, gerenciador_estados_ref);
  }
}

void coletar_maquinas_por_categoria_e_estado_trie(EstruturaDados estrutura_dados, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref)
{
  NoTrie *raiz = (NoTrie *)estrutura_dados;
  _coletar_maquinas_por_categoria_e_estado_trie_recursiva(raiz, categoria_cod, gerenciador_estados_ref);
}