#include <time.h>
#include "../../../../libs/gov_dev/gov_dev.h"
#include "../use-cases/inativar-maquina.use-case.h"
#include "../use-cases/gerar-relatorio-de-responsabilidade.use-case.h"

void exibir_interface(NoABB *raiz)
{
  int menu;
  char renamaut[17];
  clock_t inicio, fim;
  double tempo_para_operacao;

  do
  {
    menu = main_menu();

    if (menu == 2)
    {
      printf("Digite o código renamaut da máquina que será inativada: ");
      scanf("%16s", renamaut);

      inativar_maquina(raiz, renamaut);
    }

    else if (menu == 3)
    {
      printf("Digite o documento do resposavel pelas máquinas: ");
      scanf("%16s", renamaut);

      inicio = clock();
      gerar_relatorio_de_responsabilidade(raiz, renamaut);
      fim = clock();

      tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
      printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

      wait_enter("\nAperte Enter para voltar ao menu inicial\n");
    }

    else if (menu == 0)
    {
      if (wait_confirmation("Deseja realmente sair do programa? s/n\n") == 1)
      {
        break;
      }
    }

  } while (1);
}