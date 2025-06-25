#include "../../shared/services/converter-arquivo.h"
#include "services/inserir-no.service.h"
#include "services/imprimir.service.h"
#include "services/resetar-arvore.service.h"
#include "types/no.type.h"

void *inserir_wrapper(void *arvore, Registro registro)
{
    return (void *)inserir((NoABB **)&arvore, registro);
}

int main(int argc, char *argv[])
{
  NoABB *arvore = NULL;

  printf("argc %d", argc);

  converter_arquivo((void **)&arvore, argc, argv, inserir_wrapper);

  imprimirInOrdem(arvore);

  limparArvore(&arvore);

  imprimirInOrdem(arvore);
  return 0;
}