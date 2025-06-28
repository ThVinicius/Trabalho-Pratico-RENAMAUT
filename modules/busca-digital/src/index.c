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

  inicio = clock();
  converter_arquivo((void **)&arvore_trie, argc, argv, inserir_wrapper_trie);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserção dos dados dos arquivos (Árvore de Busca Digital - Trie): %.6f segundos\n", tempo_para_insercao);

  exibir_interface(
      (EstruturaDados)arvore_trie,
      (BuscarCallback)buscar_wrapper_trie,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_trie,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_trie);

  limparTrie(&arvore_trie);

  return 0;
}