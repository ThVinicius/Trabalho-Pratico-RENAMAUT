#include "inserir.service.h"

void *inserir_na_lista_encadeada_ordenada(EstruturaDados estrutura_dados, Registro maquina)
{
  ListaRegistro *cabeca = (ListaRegistro *)estrutura_dados;
  ListaRegistro *novo_no;
  ListaRegistro *atual;

  novo_no = criar_no_lista_registro_simples(maquina);
  if (novo_no == NULL)
  {
    return cabeca;
  }

  if (cabeca == NULL || strcmp(novo_no->registro.renamaut, cabeca->registro.renamaut) < 0)
  {
    novo_no->next = cabeca;
    return (void *)novo_no;
  }

  atual = cabeca;
  while (atual->next != NULL && strcmp(novo_no->registro.renamaut, atual->next->registro.renamaut) >= 0)
  {
    atual = atual->next;
  }
  novo_no->next = atual->next;
  atual->next = novo_no;

  return (void *)cabeca;
}