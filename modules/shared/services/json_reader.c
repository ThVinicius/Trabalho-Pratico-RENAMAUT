#include "json_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *parse_json_and_insert(char *filename, void *estrutura_dados, InserirCallback callback_inserir)
{
  JSON_Value *root_value;
  JSON_Object *root_object;
  JSON_Array *dados_array;
  JSON_Object *item;
  JSON_Object *loc_base;
  Registro temp_registro;
  const char *renamaut_str, *fab_str, *mod_str, *cat_str, *apl_str, *resp_str;
  const char *cidade_str, *uf_str;
  int i;
  int count = 0;

  /* Carregar o arquivo JSON */
  root_value = json_parse_file(filename);
  if (root_value == NULL)
  {
    fprintf(stderr, "Erro ao abrir ou parsear o arquivo %s\n", filename);
    return NULL;
  }

  /* Obter o objeto raiz */
  root_object = json_value_get_object(root_value);
  if (root_object == NULL)
  {
    fprintf(stderr, "Erro: raiz não é um objeto JSON\n");
    json_value_free(root_value);
    return NULL;
  }

  /* Acessar o array "dados" */
  dados_array = json_object_get_array(root_object, "dados");
  if (dados_array == NULL)
  {
    fprintf(stderr, "Erro: 'dados' não é um array\n");
    json_value_free(root_value);
    return NULL;
  }

  /* Obter o número de itens no array */
  count = json_array_get_count(dados_array);

  if (count == 0)
  {
    json_value_free(root_value);
    return estrutura_dados;
  }

  /* Preencher os registros e chamar o callback para cada um */
  for (i = 0; i < count; i++)
  {
    item = json_array_get_object(dados_array, i);

    if (item == NULL)
    {
      fprintf(stderr, "Erro: item %d não é um objeto\n", i);
      continue;
    }

    /* Popular a struct temporária */
    renamaut_str = json_object_get_string(item, "renamaut");
    if (renamaut_str)
    {
      strncpy(temp_registro.renamaut, renamaut_str, sizeof(temp_registro.renamaut) - 1);
      temp_registro.renamaut[sizeof(temp_registro.renamaut) - 1] = '\0';
    }

    fab_str = json_object_get_string(item, "fab");
    if (fab_str)
    {
      strncpy(temp_registro.fab, fab_str, sizeof(temp_registro.fab) - 1);
      temp_registro.fab[sizeof(temp_registro.fab) - 1] = '\0';
    }

    mod_str = json_object_get_string(item, "mod");
    if (mod_str)
    {
      strncpy(temp_registro.mod, mod_str, sizeof(temp_registro.mod) - 1);
      temp_registro.mod[sizeof(temp_registro.mod) - 1] = '\0';
    }

    cat_str = json_object_get_string(item, "cat");
    if (cat_str)
    {
      strncpy(temp_registro.cat, cat_str, sizeof(temp_registro.cat) - 1);
      temp_registro.cat[sizeof(temp_registro.cat) - 1] = '\0';
    }

    apl_str = json_object_get_string(item, "apl");
    if (apl_str)
    {
      strncpy(temp_registro.apl, apl_str, sizeof(temp_registro.apl) - 1);
      temp_registro.apl[sizeof(temp_registro.apl) - 1] = '\0';
    }

    temp_registro.ano = (int)json_object_get_number(item, "ano");

    resp_str = json_object_get_string(item, "resp");
    if (resp_str)
    {
      strncpy(temp_registro.resp, resp_str, sizeof(temp_registro.resp) - 1);
      temp_registro.resp[sizeof(temp_registro.resp) - 1] = '\0';
    }

    loc_base = json_object_get_object(item, "loc_base");
    if (loc_base != NULL)
    {
      cidade_str = json_object_get_string(loc_base, "cidade");
      uf_str = json_object_get_string(loc_base, "uf");

      if (cidade_str)
      {
        strncpy(temp_registro.cidade, cidade_str, sizeof(temp_registro.cidade) - 1);
        temp_registro.cidade[sizeof(temp_registro.cidade) - 1] = '\0';
      }

      if (uf_str)
      {
        strncpy(temp_registro.uf, uf_str, sizeof(temp_registro.uf) - 1);
        temp_registro.uf[sizeof(temp_registro.uf) - 1] = '\0';
      }
    }
    else
    {
      strcpy(temp_registro.cidade, "N/A");
      strcpy(temp_registro.uf, "NA");
    }

    temp_registro.status = ATIVO;

    estrutura_dados = callback_inserir(estrutura_dados, temp_registro);
  }

  /* Liberar o JSON */
  json_value_free(root_value);
  return estrutura_dados;
}