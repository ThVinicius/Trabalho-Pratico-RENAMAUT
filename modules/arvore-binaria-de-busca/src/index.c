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
#include "../../../libs/gov_dev/gov_dev.h"
#include "../../shared/services/persistencia/carregar-dados.service.h"
#include "../../shared/services/persistencia/salvar-dados.service.h"
#include "services/coletar-todos-registros.service.h"
#include "../../shared/services/inicializar-gerenciador-lista.service.h"
#include "../../shared/services/liberar-gerenciador-lista.service.h"

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
  GerenciadorListaRegistro *todos_registros_para_salvar = NULL;

  arvore = (NoABB *)carregar_dados_do_arquivo((void *)arvore, inserir_wrapper, "dados.txt");

  inicio = clock();
  converter_arquivo((void **)&arvore, argc, argv, inserir_wrapper);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserçao dos dados dos arquivos: %.6f segundos\n", tempo_para_insercao);

  wait_enter("Aperte enter para inicializar o programa");

  exibir_interface(
      (EstruturaDados)arvore,
      (BuscarCallback)buscar,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_bst);

  todos_registros_para_salvar = inicializarGerenciadorLista();
  if (todos_registros_para_salvar != NULL)
  {
    coletar_todos_registros_bst(arvore, todos_registros_para_salvar);
    salvar_dados_no_arquivo(todos_registros_para_salvar->head, "dados.txt");
    liberar_lista_registro(todos_registros_para_salvar);
    free(todos_registros_para_salvar);
  }

  limparArvore(&arvore);

  return 0;
}