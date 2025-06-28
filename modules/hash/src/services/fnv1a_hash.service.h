#include <stddef.h>

/* Definições para o algoritmo FNV-1a (para 32-bit hash) */
#define FNV_PRIME_32 16777619U
#define FNV_OFFSET_BASIS_32 2166136261U

int fnv1a_hash(const char *key);
