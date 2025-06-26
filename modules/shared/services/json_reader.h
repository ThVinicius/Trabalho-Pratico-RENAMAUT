#ifndef JSON_READER_H
#define JSON_READER_H

#include "../../../libs/parson/parson.h"
#include "../types/registro.type.h"

typedef void *(*InserirCallback)(void *estrutura_dados, Registro maquina);

/*Funções para ler o JSON e liberar memória*/
void *parse_json_and_insert(char *filename, void *estrutura_dados, InserirCallback callback_inserir);

#endif