#include "imprimir.service.h"

void imprimirInOrdem(NoABB *raiz)
{
  if (raiz != NULL)
  {
    imprimirInOrdem(raiz->esquerda);
    printf("Registro: %s, Modelo: %s\n", raiz->dados.renamaut, raiz->dados.mod);
    imprimirInOrdem(raiz->direita);
  }
}