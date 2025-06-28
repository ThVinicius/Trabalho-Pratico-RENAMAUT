#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "../../shared/types/callbacks.h"
#include "../../shared/interfaces/exibir-interface.h"

#include "../../shared/services/lista-encadeada/inserir.service.h"
#include "../../shared/services/lista-encadeada/buscar.service.h"
#include "../../shared/services/lista-encadeada/resetar-lista.service.h"
#include "services/coletar-maquinas-por-responsavel-e-status.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"

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

  inicio = clock();
  converter_arquivo((void **)&lista_encadeada, argc, argv, inserir_wrapper_lista_encadeada);
  fim = clock();

  tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto na inserção dos dados dos arquivos (Lista Encadeada): %.6f segundos\n", tempo_para_insercao);

  exibir_interface(
      (EstruturaDados)lista_encadeada,
      (BuscarCallback)buscar_wrapper_lista_encadeada,
      (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_lista_encadeada,
      (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_lista_encadeada);

  limparListaRegistro(&lista_encadeada);

  return 0;
}