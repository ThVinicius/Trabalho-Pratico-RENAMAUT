#include "printer.h"
#include <stdio.h>

void print_registros(Registro *registros, int count)
{
  int i;

  if (registros == NULL || count == 0)
  {
    printf("Nenhum registro para exibir.\n");
    return;
  }

  for (i = 0; i < count; i++)
  {
    printf("Item %d:\n", i + 1);
    printf("  renamaut: %s\n", registros[i].renamaut ? registros[i].renamaut : "N/A");
    printf("  fab: %s\n", registros[i].fab ? registros[i].fab : "N/A");
    printf("  mod: %s\n", registros[i].mod ? registros[i].mod : "N/A");
    printf("  cat: %s\n", registros[i].cat ? registros[i].cat : "N/A");
    printf("  apl: %s\n", registros[i].apl ? registros[i].apl : "N/A");
    printf("  ano: %d\n", registros[i].ano);
    printf("  resp: %s\n", registros[i].resp ? registros[i].resp : "N/A");
    printf("  loc_base:\n");
    printf("    cidade: %s\n", registros[i].cidade ? registros[i].cidade : "N/A");
    printf("    uf: %s\n", registros[i].uf ? registros[i].uf : "N/A");
    printf("\n");
  }
}