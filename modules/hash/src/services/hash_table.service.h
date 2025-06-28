#include "../types/hash_table.type.h"
#include "../../../shared/types/registro.type.h"
#include "../../../shared/services/arvore-avl/inserir-no.service.h"
#include "../../../shared/services/arvore-avl/buscar.service.h"
#include "../../../shared/services/arvore-avl/resetar-arvore.service.h"
#include "fnv1a_hash.service.h"


TabelaHash *inicializarTabelaHash();

void inserirNaTabelaHash(TabelaHash *tabela, Registro maquina);

Registro *buscarNaTabelaHash(TabelaHash *tabela, const char *renamaut);
