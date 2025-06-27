#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <stdlib.h>
#include "../types/registro.type.h"

ListaRegistro *criar_no_lista_registro(Registro registro);
void adicionar_registro_na_lista(GerenciadorListaRegistro *gerenciador_ref, Registro registro);

#endif