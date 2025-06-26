#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "services/inserir-no.service.h"
#include "services/imprimir.service.h"
#include "services/resetar-arvore.service.h"
#include "types/no.type.h"
#include "interfaces/exibir-interface.h"

void *inserir_wrapper(void *arvore, Registro registro)
{
  return (void *)inserir((NoABB **)&arvore, registro);
}

int main(int argc, char *argv[])
{
  clock_t inicio, fim;
  double tempo_para_insercao;
  NoABB *arvore = NULL;

  inicio = clock();
  converter_arquivo((void **)&arvore, argc, argv, inserir_wrapper);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserçao dos dados dos arquivos: %.6f segundos\n", tempo_para_insercao);

  exibir_interface(arvore);

  return 0;
}