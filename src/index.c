#include "print/printer.h"
#include "../libs/gov_dev/gov_dev.h"
#include "lista_encadeada/resetar.h"
#include "lista_encadeada/file-to-list.h"

int main(int argc, char* argv[])
{
  const char *name;
  Registros *lista = NULL;

  file_to_list(&lista, argc, argv);

  print_registros(lista);
  resetar_lista(&lista);
  printf("lista resetada\n");
  print_registros(lista);

  name = get_state_name_by_abbr("AC");
  printf("Estado: %s\n", name);

  return 0;
}