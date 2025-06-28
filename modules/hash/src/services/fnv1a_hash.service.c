#include "fnv1a_hash.service.h"
#include <string.h>

int fnv1a_hash(const char *key)
{
  int hash = FNV_OFFSET_BASIS_32;
  size_t len = strlen(key);
  size_t i;

  for (i = 0; i < len; i++)
  {
    hash ^= (char)key[i]; /* XOR com o byte atual */
    hash *= FNV_PRIME_32;          /* Multiplica pelo primo */
  }

  return hash;
}
