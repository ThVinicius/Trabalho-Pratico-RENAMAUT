#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "../../shared/types/callbacks.h"
#include "../../shared/interfaces/exibir-interface.h"

#include "services/inserir.service.h"
#include "services/buscar.service.h"
#include "services/resetar-arvore.service.h"
#include "services/coletar-maquinas-por-responsavel-e-status.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"
#include "types/no-trie.type.h"
#include "../../../libs/gov_dev/gov_dev.h"

#include "../../shared/services/persistencia/carregar-dados.service.h"
#include "../../shared/services/persistencia/salvar-dados.service.h"
#include "../../shared/services/inicializar-gerenciador-lista.service.h"
#include "../../shared/services/liberar-gerenciador-lista.service.h"
#include "services/coletar-todos-registros.service.h"

void *inserir_wrapper_trie(void *arvore_ptr, Registro registro)
{
  return inserirNaTrie(arvore_ptr, registro);
}

Registro *buscar_wrapper_trie(void *arvore_ptr, const char *numero_registro)
{
  return buscarNaTrie(arvore_ptr, numero_registro);
}

int main(int argc, char *argv[])
{
  clock_t inicio, fim;
  double tempo_para_insercao;
  NoTrie *arvore_trie = NULL;
  GerenciadorListaRegistro *todos_registros_para_salvar = NULL;

  arvore_trie = (NoTrie *)carregar_dados_do_arquivo((void *)arvore_trie, inserir_wrapper_trie, "dados.txt");

  inicio = clock();
  converter_arquivo((void **)&arvore_trie, argc, argv, inserir_wrapper_trie);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserção dos dados dos arquivos (Árvore de Busca Digital - Trie): %.6f segundos\n", tempo_para_insercao);

  wait_enter("Aperte enter para inicializar o programa");

  exibir_interface(
      (EstruturaDados)arvore_trie,
      (BuscarCallback)buscar_wrapper_trie,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_trie,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_trie);

  todos_registros_para_salvar = inicializarGerenciadorLista();
  if (todos_registros_para_salvar != NULL)
  {
    coletar_todos_registros_trie(arvore_trie, todos_registros_para_salvar);
    salvar_dados_no_arquivo(todos_registros_para_salvar->head, "dados.txt");
    liberar_lista_registro(todos_registros_para_salvar);
    free(todos_registros_para_salvar);
  }

  limparTrie(&arvore_trie);

  return 0;
}