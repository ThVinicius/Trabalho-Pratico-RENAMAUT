#include "salvar-dados.service.h"
#include <stdlib.h>

void salvar_dados_no_arquivo(ListaRegistro *lista_de_todos_registros, const char *nome_arquivo)
{
  FILE *pont_arq;
  ListaRegistro *atual = lista_de_todos_registros;
  int contador = 0;

  pont_arq = fopen(nome_arquivo, "w");

  if (pont_arq == NULL)
  {
    printf("Erro na abertura do arquivo '%s' para salvar dados.\n", nome_arquivo);
    return;
  }

  printf("Salvando dados no arquivo '%s'...\n", nome_arquivo);

  while (atual != NULL)
  {
    fprintf(pont_arq, "%s,%s,%s,%s,%s,%d,%s,%s,%s,%d\n",
            atual->registro.renamaut,
            atual->registro.fab,
            atual->registro.mod,
            atual->registro.cat,
            atual->registro.apl,
            atual->registro.ano,
            atual->registro.resp,
            atual->registro.cidade,
            atual->registro.uf,
            atual->registro.status);
    atual = atual->next;
    contador++;
  }

  fclose(pont_arq);
  printf("%d registros salvos com sucesso em '%s'!\n", contador, nome_arquivo);
}