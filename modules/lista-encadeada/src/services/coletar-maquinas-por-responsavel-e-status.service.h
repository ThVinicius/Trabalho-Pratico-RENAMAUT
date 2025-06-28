#include "../../../shared/types/registro.type.h"
#include "../../../shared/types/callbacks.h"
#include "../../../shared/services/adicionar-registro-na-lista.service.h"
#include <string.h>

void coletar_maquinas_por_responsavel_e_status_lista_encadeada(
    EstruturaDados estrutura_dados,
    const char *cpf_cnpj,
    GerenciadorListaRegistro *ativas_gerenciador,
    GerenciadorListaRegistro *inativas_gerenciador);