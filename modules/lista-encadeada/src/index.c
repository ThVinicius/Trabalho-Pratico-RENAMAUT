#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "../../shared/types/callbacks.h"
#include "../../shared/interfaces/exibir-interface.h"

#include "../../shared/services/lista-encadeada/inserir.service.h"
#include "../../shared/services/lista-encadeada/buscar.service.h"
#include "../../shared/services/lista-encadeada/resetar-lista.service.h"
#include "services/coletar-maquinas-por-responsavel-e-status.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"
#include "../../../libs/gov_dev/gov_dev.h"

#include "../../shared/services/persistencia/carregar-dados.service.h"
#include "../../shared/services/persistencia/salvar-dados.service.h"
#include "../../shared/services/inicializar-gerenciador-lista.service.h"
#include "../../shared/services/liberar-gerenciador-lista.service.h"
#include "services/coletar-todos-registros.service.h"

void *inserir_wrapper_lista_encadeada(void *lista_ptr, Registro registro)
{
  return inserir_na_lista_encadeada_ordenada(lista_ptr, registro);
}

Registro *buscar_wrapper_lista_encadeada(void *lista_ptr, const char *numero_registro)
{
  return buscar_na_lista_encadeada(lista_ptr, numero_registro);
}

int main(int argc, char *argv[])
{
  clock_t inicio, fim;
  double tempo_para_insercao;
  ListaRegistro *lista_encadeada = NULL;
  GerenciadorListaRegistro *todos_registros_para_salvar = NULL;

  lista_encadeada = (ListaRegistro *)carregar_dados_do_arquivo((void *)lista_encadeada, inserir_wrapper_lista_encadeada, "dados.txt");

  inicio = clock();
  converter_arquivo((void **)&lista_encadeada, argc, argv, inserir_wrapper_lista_encadeada);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserção dos dados dos arquivos (Lista Encadeada): %.6f segundos\n", tempo_para_insercao);

  wait_enter("Aperte enter para inicializar o programa");

  exibir_interface(
      (EstruturaDados)lista_encadeada,
      (BuscarCallback)buscar_wrapper_lista_encadeada,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_lista_encadeada,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_lista_encadeada);

  todos_registros_para_salvar = inicializarGerenciadorLista();
  if (todos_registros_para_salvar != NULL)
  {
    coletar_todos_registros_lista_original(lista_encadeada, todos_registros_para_salvar);
    salvar_dados_no_arquivo(todos_registros_para_salvar->head, "dados.txt");
    liberar_lista_registro(todos_registros_para_salvar);
    free(todos_registros_para_salvar);
  }

  limparListaRegistro(&lista_encadeada);

  return 0;
}