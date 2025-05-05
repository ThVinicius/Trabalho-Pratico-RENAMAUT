#include "json_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Registro *parse_json_file(char *filename, int *count)
{
  JSON_Value *root_value;
  JSON_Object *root_object;
  JSON_Array *dados_array;
  Registro *registros;

  int i;

  /*Carregar o arquivo JSON*/
  root_value = json_parse_file(filename);
  if (root_value == NULL)
  {
    fprintf(stderr, "Erro ao abrir ou parsear o arquivo %s\n", filename);
    *count = 0;
    return NULL;
  }

  /*Obter o objeto raiz*/
  root_object = json_value_get_object(root_value);
  if (root_object == NULL)
  {
    fprintf(stderr, "Erro: raiz não é um objeto JSON\n");
    json_value_free(root_value);
    *count = 0;
    return NULL;
  }

  /*Acessar o array "dados"*/
  dados_array = json_object_get_array(root_object, "dados");
  if (dados_array == NULL)
  {
    fprintf(stderr, "Erro: 'dados' não é um array\n");
    json_value_free(root_value);
    *count = 0;
    return NULL;
  }

  /*Obter o número de itens no array*/
  *count = json_array_get_count(dados_array);
  if (*count == 0)
  {
    json_value_free(root_value);
    return NULL;
  }

  /*Alocar memória para os registros*/
  registros = malloc(*count * sizeof(Registro));
  if (registros == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para registros\n");
    json_value_free(root_value);
    *count = 0;
    return NULL;
  }

  /*Preencher os registros*/
  for (i = 0; i < *count; i++)
  {
    JSON_Object *item = json_array_get_object(dados_array, i);
    JSON_Object *loc_base;

    if (item == NULL)
    {
      fprintf(stderr, "Erro: item %d não é um objeto\n", i);
      continue;
    }

    strncpy(registros[i].renamaut, json_object_get_string(item, "renamaut"), sizeof(registros[i].renamaut) - 1);
    registros[i].renamaut[sizeof(registros[i].renamaut) - 1] = '\0';

    strncpy(registros[i].fab, json_object_get_string(item, "fab"), sizeof(registros[i].fab) - 1);
    registros[i].fab[sizeof(registros[i].fab) - 1] = '\0';

    strncpy(registros[i].mod, json_object_get_string(item, "mod"), sizeof(registros[i].mod) - 1);
    registros[i].mod[sizeof(registros[i].mod) - 1] = '\0';

    strncpy(registros[i].cat, json_object_get_string(item, "cat"), sizeof(registros[i].cat) - 1);
    registros[i].cat[sizeof(registros[i].cat) - 1] = '\0';

    strncpy(registros[i].apl, json_object_get_string(item, "apl"), sizeof(registros[i].apl) - 1);
    registros[i].apl[sizeof(registros[i].apl) - 1] = '\0';

    registros[i].ano = (int)json_object_get_number(item, "ano");

    strncpy(registros[i].resp, json_object_get_string(item, "resp"), sizeof(registros[i].resp) - 1);
    registros[i].resp[sizeof(registros[i].resp) - 1] = '\0';

    loc_base = json_object_get_object(item, "loc_base");

    strncpy(registros[i].cidade, json_object_get_string(loc_base, "cidade"), sizeof(registros[i].cidade) - 1);
    registros[i].cidade[sizeof(registros[i].cidade) - 1] = '\0';

    strncpy(registros[i].uf, json_object_get_string(loc_base, "uf"), sizeof(registros[i].uf) - 1);
    registros[i].uf[sizeof(registros[i].uf) - 1] = '\0';

    registros[i].status = ATIVO;
  }

  /*Liberar o JSON*/
  json_value_free(root_value);
  return registros;
}

void free_registro(Registro *registros, int count)
{
  if (registros == NULL)
    return;

  free(registros);
}