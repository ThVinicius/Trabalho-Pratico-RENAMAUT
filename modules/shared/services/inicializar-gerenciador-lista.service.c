#include "inicializar-gerenciador-lista.service.h"

GerenciadorListaRegistro *inicializarGerenciadorLista()
{
  GerenciadorListaRegistro *gerenciador = (GerenciadorListaRegistro *)malloc(sizeof(GerenciadorListaRegistro));

  gerenciador->head = NULL;
  gerenciador->tail = NULL;

  return gerenciador;
}