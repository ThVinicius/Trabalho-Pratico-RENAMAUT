#include "buscar.service.h"
#include "criar-no.service.h"

Registro *buscarNaTrie(EstruturaDados arvore_trie, const char *numero_registro)
{
  NoTrie *atual;
  NoTrie *raiz = (NoTrie *)arvore_trie;
  int nivel;
  int comprimento_chave = strlen(numero_registro);
  int indice;

  if (raiz == NULL)
  {
    return NULL; /* Árvore vazia */
  }

  atual = raiz;

  /* Percorre a Trie seguindo a chave de busca */
  for (nivel = 0; nivel < comprimento_chave; nivel++)
  {
    indice = (unsigned char)numero_registro[nivel];
    if (atual->children[indice] == NULL)
    {
      return NULL; /* Caminho não existe, chave não encontrada */
    }
    atual = atual->children[indice];
  }

  /* Se o nó atual existe e marca o fim de uma chave, a máquina foi encontrada. */
  if (atual != NULL && atual->is_end_of_key)
  {
    return &(atual->dados);
  }

  return NULL; /* Chave não encontrada ou não é o final de uma chave válida */
}