#include "criar-no.service.h"

NoTrie *criarNoTrie()
{
  NoTrie *novoNo = (NoTrie *)malloc(sizeof(NoTrie));
  if (novoNo == NULL)
  {
    return NULL;
  }

  memset(novoNo->children, 0, sizeof(novoNo->children));
  novoNo->is_end_of_key = false;

  return novoNo;
}