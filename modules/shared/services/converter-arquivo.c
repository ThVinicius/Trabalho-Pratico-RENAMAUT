#include "converter-arquivo.h"
#include <stdio.h>

void converter_arquivo(void **estrutura_dados, int argc, char *argv[], InserirCallback callback_inserir)
{
  int i;
  for (i = 1; i < argc; i++)
  {
    *estrutura_dados = parse_json_and_insert(argv[i], *estrutura_dados, callback_inserir);
  }
}