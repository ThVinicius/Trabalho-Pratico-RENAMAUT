#include "leitura_arquivo_json/json_reader.h"
#include "print/printer.h"
#include "../libs/gov_dev/gov_dev.h"
#include "lista_encadeada/add.h"
#include "lista_encadeada/resetar.h"

int main()
{
  int count = 0;
  const char *name;
  int i;
  Registros *lista = NULL;

  Registro *registros = parse_json_file("src/assets/exemplo_20.ERMAUF", &count);
  for (i = 0; i < count; i++)
  {
    add_registro(&lista, &registros[i]);
  }
  free_registro(registros, count);

  print_registros(lista);
  resetar_lista(&lista);
  printf("lista resetada\n");
  print_registros(lista);

  name = get_state_name_by_abbr("AC");
  printf("Estado: %s\n", name);

  return 0;
}