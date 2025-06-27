#include <stdio.h>
#include "../../types/registro.type.h"
#include "../imprimir-lista-registro.service.h"
#include "../imprimir-maquina-formatada.service.h"

void imprimir_relatorio_de_responsabilidade(ListaRegistro *lista_maquina_ativa, ListaRegistro *lista_maquina_inativa, const char *cpf_cnpj);