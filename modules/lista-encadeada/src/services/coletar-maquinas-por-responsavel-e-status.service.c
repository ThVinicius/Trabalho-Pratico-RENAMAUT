#include "coletar-maquinas-por-responsavel-e-status.service.h"

void coletar_maquinas_por_responsavel_e_status_lista_encadeada(
    EstruturaDados estrutura_dados,
    const char *cpf_cnpj,
    GerenciadorListaRegistro *ativas_gerenciador,
    GerenciadorListaRegistro *inativas_gerenciador)
{
  ListaRegistro *atual = (ListaRegistro *)estrutura_dados;

  while (atual != NULL)
  {
    if (strcmp(atual->registro.resp, cpf_cnpj) == 0)
    {
      if (atual->registro.status == ATIVO)
      {
        adicionar_registro_na_lista(ativas_gerenciador, atual->registro);
      }
      else
      {
        adicionar_registro_na_lista(inativas_gerenciador, atual->registro);
      }
    }
    atual = atual->next;
  }
}