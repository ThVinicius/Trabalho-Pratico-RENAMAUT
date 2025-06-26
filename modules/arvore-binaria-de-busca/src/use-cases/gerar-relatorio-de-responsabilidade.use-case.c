#include "gerar-relatorio-de-responsabilidade.use-case.h"

void gerar_relatorio_de_responsabilidade(NoABB *raiz, const char *cpf_cnpj)
{
  GerenciadorListaRegistro *ativas_gerenciador = inicializarGerenciadorLista();
  GerenciadorListaRegistro *inativas_gerenciador = inicializarGerenciadorLista();

  coletar_maquinas_por_responsavel_e_status(raiz, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);

  imprimir_relatorio_de_responsabilidade(ativas_gerenciador->head, inativas_gerenciador->head, cpf_cnpj);

  liberar_lista_registro(&ativas_gerenciador);
  liberar_lista_registro(&inativas_gerenciador);

  free(ativas_gerenciador);
  free(inativas_gerenciador);
}