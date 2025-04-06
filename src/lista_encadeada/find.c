#include <string.h>
#include "find.h"

Registro *find_registro(Registros *lista, char *renamaut)
{
  Registros *current = lista;

  while (current != NULL)
  {
    if (strcmp(current->registro.renamaut, renamaut) == 0)
    {
      return &current->registro;
    }
    current = current->next;
  }

  return NULL;
}