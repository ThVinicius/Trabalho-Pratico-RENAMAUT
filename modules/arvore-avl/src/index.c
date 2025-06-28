#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "services/inserir-no.service.h"
#include "services/buscar.service.h"
#include "services/resetar-arvore.service.h"
#include "types/no-avl.type.h"
#include "../../shared/interfaces/exibir-interface.h"
#include "../../shared/types/callbacks.h"
#include "../../../libs/gov_dev/gov_dev.h"

#include "services/coletar-maquinas-por-responsavel-e-status.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"

void *inserir_wrapper_avl(void *arvore_ptr, Registro registro)
{
  return inserirAVL(arvore_ptr, registro);
}

int main(int argc, char *argv[])
{
  clock_t inicio, fim;
  double tempo_para_insercao;
  NoAVL *arvore_avl = NULL;

  inicio = clock();
  converter_arquivo((void **)&arvore_avl, argc, argv, inserir_wrapper_avl);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserção dos dados dos arquivos (AVL): %.6f segundos\n", tempo_para_insercao);

  wait_enter("Aperte enter para inicializar o programa");

  exibir_interface(
      (EstruturaDados)arvore_avl,
      (BuscarCallback)buscarAVL,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_avl,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_avl);

  limparArvoreAVL(&arvore_avl);

  return 0;
}