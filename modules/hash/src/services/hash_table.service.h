#include "../types/hash_table.type.h"
#include "../../../shared/types/registro.type.h"
#include "../../../shared/services/lista-encadeada/buscar.service.h"
#include "../../../shared/services/adicionar-registro-na-lista.service.h"
#include "../../../shared/services/inicializar-gerenciador-lista.service.h"
#include "../../../shared/services/liberar-gerenciador-lista.service.h"
#include "fnv1a_hash.service.h"

TabelaHash *inicializarTabelaHash();

void inserirNaTabelaHash(TabelaHash *tabela, Registro maquina);

Registro *buscarNaTabelaHash(TabelaHash *tabela, const char *renamaut);