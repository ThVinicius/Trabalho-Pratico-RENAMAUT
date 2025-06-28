#ifndef JSON_READER_H
#define JSON_READER_H

#include "../../../libs/parson/parson.h"
#include "../types/registro.type.h"
#include "../types/callbacks.h"


/*Funções para ler o JSON e liberar memória*/
void *parse_json_and_insert(char *filename, void **estrutura_dados, InserirCallback callback_inserir);

#endif