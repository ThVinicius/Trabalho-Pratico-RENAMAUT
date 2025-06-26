#include <time.h>
#include "inativar-maquina.use-case.h"
#include "../../../../libs/gov_dev/gov_dev.h"

void inativar_maquina(NoABB *raiz, const char *renamaut)
{
  clock_t inicio, fim;
  double tempo_para_operacao;
  NoABB *no;

  inicio = clock();
  no = buscar(raiz, renamaut);
  fim = clock();

  tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

  if (no == NULL)
  {
    printf("Máquina não encontrada!\n");
  }
  else
  {
    if (no->dados.status == INATIVO)
    {
      printf("\n--- Essa máquina já se encontra inativa ---\n");
      wait_enter("\nAperte Enter para voltar ao menu inicial\n");
    }
    else
    {
      printf("\n--- Máquina encontrada ---\n");
      printf("\n");
      imprimir_maquina_formatada(no->dados);
      printf("\n--------------------------\n");

      if (wait_confirmation("Deseja realmente inativar essa máquina? s/n") == 1)
      {
        no->dados.status = INATIVO;
      }
    }
  }
}
