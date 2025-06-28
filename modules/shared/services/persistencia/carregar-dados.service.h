#include "../../../shared/types/registro.type.h"
#include "../../../shared/types/callbacks.h"
#include <stdio.h>

void *carregar_dados_do_arquivo(void *estrutura_dados_ref, InserirCallback inserir_fn, const char *nome_arquivo);