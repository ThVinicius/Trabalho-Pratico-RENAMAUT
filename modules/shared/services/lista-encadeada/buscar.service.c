#include "buscar.service.h"

Registro *buscar_na_lista_encadeada(EstruturaDados estrutura_dados, const char *numero_registro)
{
  ListaRegistro *current = (ListaRegistro *)estrutura_dados;

  while (current != NULL)
  {
    if (strcmp(current->registro.renamaut, numero_registro) == 0)
    {
      return &current->registro;
    }
    current = current->next;
  }

  return NULL;
}