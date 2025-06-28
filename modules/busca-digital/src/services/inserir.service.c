#include "inserir.service.h"
#include "criar-no.service.h"

void *inserirNaTrie(EstruturaDados arvore_trie, Registro maquina)
{
  NoTrie *raiz = (NoTrie *)arvore_trie;
  NoTrie *atual;
  int nivel;
  int comprimento_chave = strlen(maquina.renamaut);
  int indice;

  /* Caso 1: Árvore vazia. Cria o nó raiz se for NULL. */
  if (raiz == NULL)
  {
    raiz = criarNoTrie();
    if (raiz == NULL)
    {
      return NULL;
    }
  }

  atual = raiz;

  /* Percorre a Trie, criando nós se necessário */
  for (nivel = 0; nivel < comprimento_chave; nivel++)
  {
    indice = (unsigned char)maquina.renamaut[nivel];
    if (atual->children[indice] == NULL)
    {
      atual->children[indice] = criarNoTrie();
      if (atual->children[indice] == NULL)
      {
        return raiz;
      }
    }
    atual = atual->children[indice];
  }

  /* Após percorrer toda a chave, o nó 'atual' é onde a chave deveria terminar. */
  if (atual->is_end_of_key)
  {
    printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
    return raiz;
  }
  else
  {
    /* Marca este nó como o final de uma chave e armazena os dados. */
    atual->is_end_of_key = true;
    atual->dados = maquina;
  }

  return raiz;
}