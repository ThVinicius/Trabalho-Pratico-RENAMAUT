#include "imprimir-relatorio-categoria.service.h"
#include "../../../../libs/gov_dev/gov_dev.h"

void imprimirRelatorioCategoria(GerenciadorListaEstados *gerenciador_estados, const char *categoria_cod)
{
  NoEstadoRelatorioCategoria *atual_estado = gerenciador_estados->head;
  const char *nome_categoria = get_category_name_by_code(categoria_cod);

  printf("\n--- Relatório de Máquinas Ativas por Categoria: %s ---\n", nome_categoria);

  if (atual_estado == NULL)
  {
    printf("\nNenhuma máquina ativa encontrada para esta categoria.\n");
  }
  else
  {
    while (atual_estado != NULL)
    {
      printf("\n*** Estado: %s ***\n", atual_estado->uf);
      imprimir_lista_registro(atual_estado->maquinas_no_estado.head);
      atual_estado = atual_estado->prox;
    }
  }
  printf("\n--- Fim do Relatório de Categoria ---\n");
}