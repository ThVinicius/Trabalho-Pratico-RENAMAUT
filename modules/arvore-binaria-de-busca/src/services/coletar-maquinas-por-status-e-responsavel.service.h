#include <string.h>
#include "../types/no.type.h"
#include "../../../shared/types/registro.type.h"
#include "../../../shared/services/adicionar-registro-na-lista.service.h"

void coletar_maquinas_por_responsavel_e_status(NoABB *raiz, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador);