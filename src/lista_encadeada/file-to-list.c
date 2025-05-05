#include "file-to-list.h"
#include "../types/registro.type.h"
#include "../leitura_arquivo_json/json_reader.h"
#include "../lista_encadeada/add.h"

void file_to_list(Registros **lista, int argc, char *argv[])
{
  int i, j;

  for (i = 1; i < argc; i++)
  {
    int count = 0;
    Registro *registros = parse_json_file(argv[i], &count);

    for (j = 0; j < count; j++)
    {
      add_registro(lista, &registros[j]);
    }
    free_registro(registros, count);
  }
}