#ifndef HASH_TABLE_TYPE_H
#define HASH_TABLE_TYPE_H

#include "../../../shared/types/registro.type.h"

#define TAMANHO_TABELA_HASH 100003

typedef struct
{
  GerenciadorListaRegistro *baldes[TAMANHO_TABELA_HASH];
} TabelaHash;

#endif