#include "imprimir-maquina.service.h"

void imprimirMaquinaFormatada(Registro *maquina)
{
  if (maquina == NULL)
  {
    return;
  }

  const char *status_str = (maquina->status == ATIVO) ? "ativo" : "inativo";

  printf("%s;%s;%s;%d;%s;%s %s\n",
         maquina->renamaut,
         maquina->resp,
         maquina->mod,
         maquina->ano,
         status_str,
         maquina->cidade,
         maquina->uf);
}