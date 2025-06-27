#include <time.h>
#include "exibir-maquina-por-renamaut.use-case.h"
#include "../../../../libs/gov_dev/gov_dev.h"

void exibir_maquina_por_renamaut(NoABB *raiz, const char *renamaut)
{
  clock_t inicio, fim;
  double tempo_para_operacao;
  NoABB *no;

  inicio = clock();
  no = buscar(raiz, renamaut);
  fim = clock();

  tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;

  if (no == NULL)
  {
    printf("\nMáquina não encontrada!\n");
  }
  else
  {
    printf("\n--- Máquina encontrada ---\n");
    printf("\n");
    imprimir_maquina_formatada(no->dados);
    printf("\n--------------------------\n");
  }

  printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

  wait_enter("\nAperte Enter para voltar ao menu inicial\n");
}