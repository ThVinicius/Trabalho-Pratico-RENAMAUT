#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "services/inserir-no.service.h"
#include "services/resetar-arvore.service.h"
#include "types/no.type.h"
#include "../../shared/interfaces/exibir-interface.h"
#include "../../shared/types/callbacks.h"
#include "services/buscar.service.h"
#include "services/coletar-maquinas-por-status-e-responsavel.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"

void *inserir_wrapper(void *arvore_ptr, Registro registro)
{
  NoABB *current_root = (NoABB *)arvore_ptr;
  NoABB *new_root = inserir(current_root, registro);
  return (void *)new_root;
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

  exibir_interface(
      (EstruturaDados)arvore,
      (BuscarCallback)buscar,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_bst);

  limparArvore(&arvore);

  return 0;
}