#ifndef JSON_READER_H
#define JSON_READER_H

#include "../../libs/parson/parson.h"
#include "../types/registro.type.h"

/*Funções para ler o JSON e liberar memória*/
Registro *parse_json_file(char *filename, int *count);
void free_registro(Registro *registros, int count);

#endif