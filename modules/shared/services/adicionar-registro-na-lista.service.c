#include "adicionar-registro-na-lista.service.h"

ListaRegistro *criar_no_lista_registro(Registro registro)
{
  ListaRegistro *novoNo = (ListaRegistro *)malloc(sizeof(ListaRegistro));
  if (novoNo == NULL)
  {
    return NULL;
  }

  novoNo->registro = registro;
  novoNo->next = NULL;
  return novoNo;
}

void adicionar_registro_na_lista(GerenciadorListaRegistro **gerenciador_ref, Registro registro)
{
  ListaRegistro *novoNo = criar_no_lista_registro(registro);
  if (novoNo == NULL)
  {
    return;
  }

  if ((*gerenciador_ref)->head == NULL)
  {
    (*gerenciador_ref)->head = novoNo;
    (*gerenciador_ref)->tail = novoNo;
  }
  else
  {
    (*gerenciador_ref)->tail->next = novoNo;
    (*gerenciador_ref)->tail = novoNo;
  }
}