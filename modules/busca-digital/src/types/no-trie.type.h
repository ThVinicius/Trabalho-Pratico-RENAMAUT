#ifndef NO_TRIE_TYPE_H
#define NO_TRIE_TYPE_H

#include "../../../shared/types/registro.type.h"
#include <stdbool.h>

#define ALPHABET_SIZE 256

typedef struct NoTrie
{
  Registro dados;
  struct NoTrie *children[ALPHABET_SIZE];
  bool is_end_of_key;
} NoTrie;

#endif