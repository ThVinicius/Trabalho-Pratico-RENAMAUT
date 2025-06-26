#include "../../../../libs/gov_dev/gov_dev.h"
#include "../use-cases/inativar-maquina.use-case.h"
#include "../use-cases/gerar-relatorio-de-responsabilidade.use-case.h"

void exibir_interface(NoABB *raiz)
{
  int menu;
  char renamaut[17];

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

      gerar_relatorio_de_responsabilidade(raiz, renamaut);
      wait_enter("Aperte Enter para voltar ao menu inicial");
    }

    else if (menu == 0)
    {
      if (wait_confirmation("Deseja realmente sair do programa? s/n") == 1)
      {
        break;
      }
    }

  } while (1);
}