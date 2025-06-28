#include "carregar-dados.service.h"
#include <stdlib.h>
#include <string.h>
#include "../adicionar-registro-na-lista.service.h"
#include "../imprimir-maquina-formatada.service.h"

static char *safe_strtok(char *str, const char *delim, char **saveptr)
{
  char *result;
  if (str != NULL)
  {
    *saveptr = str;
  }
  if (*saveptr == NULL || **saveptr == '\0')
  {
    return NULL;
  }

  result = *saveptr;
  while (**saveptr != '\0' && strchr(delim, **saveptr) == NULL)
  {
    (*saveptr)++;
  }

  if (**saveptr != '\0')
  {
    **saveptr = '\0';
    (*saveptr)++;
  }
  return result;
}

void *carregar_dados_do_arquivo(void *estrutura_dados_ref, InserirCallback inserir_fn, const char *nome_arquivo)
{
  FILE *pont_arq;
  Registro novo_registro;
  char linha[512];
  char *token;
  char *saveptr;

  pont_arq = fopen(nome_arquivo, "r");

  if (pont_arq == NULL)
  {
    printf("Erro ao abrir o arquivo %s. Criando um novo arquivo se ele não existe.\n", nome_arquivo);
    return estrutura_dados_ref;
  }

  printf("Lendo dados do arquivo '%s'...\n", nome_arquivo);

  while (fgets(linha, sizeof(linha), pont_arq))
  {
    linha[strcspn(linha, "\n")] = '\0';

    /* Usando safe_strtok para compatibilidade C90 e reentrância */
    token = safe_strtok(linha, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.renamaut, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.fab, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.mod, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.cat, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.apl, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    novo_registro.ano = atoi(token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.resp, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.cidade, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    strcpy(novo_registro.uf, token);

    token = safe_strtok(NULL, ",", &saveptr);
    if (!token)
      continue;
    novo_registro.status = atoi(token);

    /* Chama a função de inserção fornecida pela estrutura de dados específica */
    estrutura_dados_ref = inserir_fn(estrutura_dados_ref, novo_registro);
  }

  fclose(pont_arq);
  printf("Dados de '%s' carregados com sucesso!\n", nome_arquivo);
  return estrutura_dados_ref;
}