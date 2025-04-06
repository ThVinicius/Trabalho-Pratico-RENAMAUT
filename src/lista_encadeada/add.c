#include <stdlib.h>
#include "add.h"
#include "../types/registro.type.h"

void add_registro(Registros **lista, Registro *registro)
{
  Registros *new_registro = (Registros *)malloc(sizeof(Registros));
  new_registro->registro = *registro;
  new_registro->next = NULL;

  if (*lista == NULL)
  {
    (*lista) = new_registro;
  }
  else
  {
    Registros *last = *lista;

    while (last->next != NULL)
    {
      last = last->next;
    }

    last->next = new_registro;
  }
}