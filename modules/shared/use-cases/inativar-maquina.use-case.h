#include <stdio.h>
#include "../services/imprimir-maquina-formatada.service.h"
#include "../types/callbacks.h" 
#include "../services/change-machine-status.h"

void inativar_maquina(EstruturaDados estrutura_dados, BuscarCallback buscar_fn, const char *renamaut);
