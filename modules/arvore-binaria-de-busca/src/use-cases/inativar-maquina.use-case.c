#include "inativar-maquina.use-case.h"
#include "../../../../libs/gov_dev/gov_dev.h"

void inativar_maquina(NoABB *raiz, const char *renamaut)
{
  NoABB *no = buscar(raiz, renamaut);

  if (no == NULL)
  {
    printf("Máquina não encontrada!\n");
  }
  else
  {
    printf ("\n--- Máquina encontrada ---\n");
    printf("\n");
    imprimir_maquina_formatada(no->dados);
    printf ("\n--------------------------\n");

    if (wait_confirmation("Deseja realmente mudar o status dessa máquina? s/n") == 1)
    {
      no->dados.status = INATIVO;
    }
  }
}
