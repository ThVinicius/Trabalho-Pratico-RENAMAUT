#include "coletar-maquinas-por-categoria-e-estado.service.h"

void coletar_maquinas_por_categoria_e_estado_lista_encadeada(
    EstruturaDados estrutura_dados,
    const char *categoria_cod,
    GerenciadorListaEstados *gerenciador_estados_ref)
{
  ListaRegistro *atual = (ListaRegistro *)estrutura_dados;

  while (atual != NULL)
  {
    if (atual->registro.status == ATIVO && strcmp(atual->registro.cat, categoria_cod) == 0)
    {
      NoEstadoRelatorioCategoria *no_estado_atual;
      no_estado_atual = adicionarEstadoOrdenadoRelatorioCategoria(gerenciador_estados_ref, atual->registro.uf);

      if (no_estado_atual != NULL)
      {
        adicionar_registro_na_lista(&(no_estado_atual->maquinas_no_estado), atual->registro);
      }
    }
    atual = atual->next;
  }
}