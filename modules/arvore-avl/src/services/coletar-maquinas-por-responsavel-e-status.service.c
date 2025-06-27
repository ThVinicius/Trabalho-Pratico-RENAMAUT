#include "./coletar-maquinas-por-responsavel-e-status.service.h"
#include <string.h>

void coletar_maquinas_por_responsavel_e_status_avl(EstruturaDados estrutura_dados, const char *cpf_cnpj, GerenciadorListaRegistro *ativas_gerenciador, GerenciadorListaRegistro *inativas_gerenciador)
{
  NoAVL *raiz = (NoAVL *)estrutura_dados;

  if (raiz == NULL)
  {
    return;
  }

  coletar_maquinas_por_responsavel_e_status_avl((EstruturaDados)raiz->esquerda, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);

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

  coletar_maquinas_por_responsavel_e_status_avl((EstruturaDados)raiz->direita, cpf_cnpj, ativas_gerenciador, inativas_gerenciador);
}