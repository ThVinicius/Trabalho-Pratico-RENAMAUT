#include <time.h>
#include "inativar-maquina.use-case.h"
#include "../../../libs/gov_dev/gov_dev.h"

void inativar_maquina(EstruturaDados estrutura_dados, BuscarCallback buscar_fn, const char *renamaut)
{
  clock_t inicio, fim;
  double tempo_para_operacao_busca;
  double tempo_para_operacao_inativacao;
  Registro *registro_para_inativar;

  inicio = clock();
  registro_para_inativar = buscar_fn(estrutura_dados, renamaut);
  fim = clock();

  tempo_para_operacao_busca = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("\nTempo de CPU gasto na busca: %.6f segundos\n", tempo_para_operacao_busca);

  if (registro_para_inativar == NULL)
  {
    printf("Máquina não encontrada!\n");
  }
  else
  {
    if (registro_para_inativar->status == INATIVO)
    {
      printf("\n--- Essa máquina já se encontra inativa ---\n");
    }
    else
    {
      printf("\n--- Máquina encontrada ---\n");
      printf("\n");
      imprimir_maquina_formatada(*registro_para_inativar);
      printf("\n--------------------------\n");

      if (wait_confirmation("Deseja realmente inativar essa máquina? s/n") == 1)
      {
        inicio = clock();
        change_machine_status(registro_para_inativar, INATIVO);
        fim = clock();
        tempo_para_operacao_inativacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\nTempo de CPU gasto na inativação: %.6f segundos\n", tempo_para_operacao_inativacao);
        printf("\nMáquina inativada com sucesso.\n");
      }
      else
      {
        printf("\nOperação de inativação cancelada.\n");
      }
    }
  }
  wait_enter("\nAperte Enter para voltar ao menu inicial\n");
}