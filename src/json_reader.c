#include "json_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *my_strdup(const char *str)
{
  char *dup;

  if (!str)
    return NULL;
  dup = malloc(strlen(str) + 1);
  if (dup)
    strcpy(dup, str);
  return dup;
}

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
    fprintf(stderr, "Erro ao abrir ou parsear o arquivo JSON\n");
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

    /*Função auxiliar para duplicar strings (evita usar diretamente os ponteiros do JSON)*/
    registros[i].renamaut = my_strdup(json_object_get_string(item, "renamaut"));
    registros[i].fab = my_strdup(json_object_get_string(item, "fab"));
    registros[i].mod = my_strdup(json_object_get_string(item, "mod"));
    registros[i].cat = my_strdup(json_object_get_string(item, "cat"));
    registros[i].apl = my_strdup(json_object_get_string(item, "apl"));
    registros[i].ano = (int)json_object_get_number(item, "ano");
    registros[i].resp = my_strdup(json_object_get_string(item, "resp"));

    /*Acessar o subobjeto "loc_base"*/
    loc_base = json_object_get_object(item, "loc_base");
    registros[i].cidade = my_strdup(json_object_get_string(loc_base, "cidade"));
    registros[i].uf = my_strdup(json_object_get_string(loc_base, "uf"));
  }

  /*Liberar o JSON*/
  json_value_free(root_value);
  return registros;
}

void free_registro(Registro *registros, int count)
{
  int i;

  if (registros == NULL)
    return;

  for (i = 0; i < count; i++)
  {
    free(registros[i].renamaut);
    free(registros[i].fab);
    free(registros[i].mod);
    free(registros[i].cat);
    free(registros[i].apl);
    free(registros[i].resp);
    free(registros[i].cidade);
    free(registros[i].uf);
  }
  free(registros);
}