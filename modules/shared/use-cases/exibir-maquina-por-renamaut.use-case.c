#include <time.h>
#include "exibir-maquina-por-renamaut.use-case.h"
#include "../../../libs/gov_dev/gov_dev.h"

void exibir_maquina_por_renamaut(EstruturaDados estrutura_dados, BuscarCallback buscar_fn, const char *renamaut)
{
  clock_t inicio, fim;
  double tempo_para_operacao;
  Registro *registro_encontrado;

  inicio = clock();
  registro_encontrado = buscar_fn(estrutura_dados, renamaut);
  fim = clock();

  tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;

  if (registro_encontrado == NULL)
  {
    printf("\nMáquina não encontrada!\n");
  }
  else
  {
    printf("\n--- Máquina encontrada ---\n");
    printf("\n");
    imprimir_maquina_formatada(*registro_encontrado);
    printf("\n--------------------------\n");
  }

  printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

  wait_enter("\nAperte Enter para voltar ao menu inicial\n");
}