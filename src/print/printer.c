#include "printer.h"
#include <stdio.h>

void print_registros(Registros *registros)
{
  Registros *atual = registros;

  if (atual == NULL)
  {
    printf("Nenhum registro para exibir.\n");
    return;
  }

  while (atual != NULL)
  {
    printf("  renamaut: %s\n", atual->registro.renamaut);
    printf("  fab: %s\n", atual->registro.fab);
    printf("  mod: %s\n", atual->registro.mod);
    printf("  cat: %s\n", atual->registro.cat);
    printf("  apl: %s\n", atual->registro.apl);
    printf("  ano: %d\n", atual->registro.ano);
    printf("  resp: %s\n", atual->registro.resp);
    printf("  loc_base:\n");
    printf("    cidade: %s\n", atual->registro.cidade);
    printf("    uf: %s\n", atual->registro.uf);
    printf("\n");

    atual = atual->next;
  }
}