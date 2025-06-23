#include "print/printer.h"
#include "../libs/gov_dev/gov_dev.h"
#include "lista_encadeada/resetar.h"
#include "lista_encadeada/file-to-list.h"
#include "lista_encadeada/salvar-dados.h"
#include "lista_encadeada/carregar-dados.h"

int main(int argc, char* argv[])
{
  const char *name;
  Registros *lista = NULL;
	
  file_to_list(&lista, argc, argv);
  carregar_dados(&lista);
  print_registros(lista);
  salvar_dados(lista);

  name = get_state_name_by_abbr("AC");
  printf("Estado: %s\n", name);

  return 0;
}
