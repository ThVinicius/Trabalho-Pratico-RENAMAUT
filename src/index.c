#include "print/printer.h"
#include "../libs/gov_dev/gov_dev.h"
#include "lista_encadeada/resetar.h"
#include "lista_encadeada/file-to-list.h"
#include "lista_encadeada/salvar-dados.h"
#include "lista_encadeada/carregar-dados.h"
#include "shared/responsibility_report.h"
#include "shared/category_report.h"

int main(int argc, char *argv[])
{
  Registros *lista = NULL;
	
  file_to_list(&lista, argc, argv);
  carregar_dados(&lista);
  print_registros(lista);
  salvar_dados(lista);

  gerar_relatorio_responsabilidade(lista, "98761388718");
  gerar_relatorio_categoria(lista, "460");

  return 0;
}
