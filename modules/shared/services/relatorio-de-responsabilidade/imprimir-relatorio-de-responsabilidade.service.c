#include "imprimir-relatorio-de-responsabilidade.service.h"

void imprimir_relatorio_de_responsabilidade(ListaRegistro *lista_maquina_ativa, ListaRegistro *lista_maquina_inativa, const char *cpf_cnpj)
{
  printf("\n--- Relatório de Responsabilidade para CPF/CNPJ: %s ---\n", cpf_cnpj);

  printf("\n*** Máquinas Ativas ***\n");
  imprimir_lista_registro(lista_maquina_ativa);

  printf("\n*** Máquinas Inativas ***\n");
  imprimir_lista_registro(lista_maquina_inativa);

  printf("\n--- Fim do Relatório de Responsabilidade ---\n");
}