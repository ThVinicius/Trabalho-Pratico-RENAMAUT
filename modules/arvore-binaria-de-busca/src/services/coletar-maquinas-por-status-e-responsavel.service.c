#include "coletar-maquinas-por-status-e-responsavel.service.h"

void coletar_maquinas_por_responsavel_e_status(NoABB *raiz, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  if (raiz == NULL)
  {
    return;
  }

  coletar_maquinas_por_responsavel_e_status(raiz->esquerda, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);

  if (strcmp(raiz->dados.resp, cpf_cnpj) == 0)
  {
    if (raiz->dados.status == ATIVO)
    {
      adicionar_registro_na_lista(ativas_gerenciador, raiz->dados);
    }
    else
    {
      adicionar_registro_na_lista(inativas_gerenciador, raiz->dados);
    }
  }

  coletar_maquinas_por_responsavel_e_status(raiz->direita, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
}