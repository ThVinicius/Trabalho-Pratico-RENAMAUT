#include "imprimir-maquina-formatada.service.h"

void imprimir_maquina_formatada(Registro maquina)
{
  const char *status_str;

  status_str = (maquina.status == ATIVO) ? "ativo" : "inativo";

  printf("%s;%s;%s;%d;%s;%s %s\n",
         maquina.renamaut,
         maquina.resp,
         maquina.mod,
         maquina.ano,
         status_str,
         maquina.cidade,
         maquina.uf);
}