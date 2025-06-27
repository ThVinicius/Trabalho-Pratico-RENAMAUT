#include <time.h>
#include "../../../../libs/gov_dev/gov_dev.h"
#include "../use-cases/inativar-maquina.use-case.h"
#include "../use-cases/gerar-relatorio-de-responsabilidade.use-case.h"
#include "../use-cases/gerar-relatorio-de-categoria.use-case.h"
#include "../use-cases/exibir-maquina-por-renamaut.use-case.h"

void exibir_interface(NoABB *raiz)
{
  int menu;
  char input_buffer[20];
  clock_t inicio, fim;
  double tempo_para_operacao;

  do
  {
    menu = main_menu();

    if (menu == SEARCH_OPTION)
    {
      int c;
      printf("Digite o código renamaut da máquina que deseja vizualizar: ");
      scanf("%16s", input_buffer);
      while ((c = getchar()) != '\n' && c != EOF)
        ;

      exibir_maquina_por_renamaut(raiz, input_buffer);
    }

    else if (menu == CHANGE_STATUS_OPTION)
    {
      int c;
      printf("Digite o código renamaut da máquina que será inativada: ");
      scanf("%16s", input_buffer);
      while ((c = getchar()) != '\n' && c != EOF)
        ;

      inativar_maquina(raiz, input_buffer);
    }

    else if (menu == RESPONSABILITY_REPORT_OPTION)
    {
      int c;
      printf("Digite o documento do responsavel pelas máquinas (CPF/CNPJ): ");
      scanf("%16s", input_buffer);
      while ((c = getchar()) != '\n' && c != EOF)
        ;

      inicio = clock();
      gerar_relatorio_de_responsabilidade(raiz, input_buffer);
      fim = clock();

      tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
      printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

      wait_enter("\nAperte Enter para voltar ao menu inicial\n");
    }

    else if (menu == CATEGORY_REPORT_OPTION)
    {
      int c;
      show_categories_by_acronym();
      printf("\nDigite o código de 6 letras de uma das categorias acima: ");
      scanf("%6s", input_buffer);
      while ((c = getchar()) != '\n' && c != EOF)
        ;

      inicio = clock();
      gerar_relatorio_de_categoria(raiz, input_buffer);
      fim = clock();

      tempo_para_operacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
      printf("\nTempo de CPU gasto na operação: %.6f segundos\n", tempo_para_operacao);

      wait_enter("\nAperte Enter para voltar ao menu inicial\n");
    }

    else if (menu == EXIT_SYSTEM)
    {
      break;
    }

  } while (1);
}