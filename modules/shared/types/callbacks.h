#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "registro.type.h"

typedef void *EstruturaDados;

typedef EstruturaDados (*InserirCallback)(EstruturaDados estrutura_dados, Registro maquina);

typedef Registro *(*BuscarCallback)(EstruturaDados estrutura_dados, const char *numero_registro);

typedef void (*ColetarMaquinasPorStatusEResponsavelCallback)(EstruturaDados estrutura_dados, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador);

typedef void (*ColetarMaquinasPorCategoriaEEstadoCallback)(EstruturaDados estrutura_dados, const char *categoria_cod, GerenciadorListaEstados *gerenciador_estados_ref);

#endif