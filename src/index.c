#include "print/printer.h"
#include "../libs/gov_dev/gov_dev.h"
#include "lista_encadeada/resetar.h"
#include "lista_encadeada/file-to-list.h"
#include "shared/responsibility_report.h"

int main(int argc, char *argv[])
{
  const char *name;
  Registros *lista = NULL;

  file_to_list(&lista, argc, argv);

  gerar_relatorio_responsabilidade(lista, "98761388718");

  return 0;
}