#include "../../types/registro.type.h"

GerenciadorListaEstados *inicializarGerenciadorListaEstados();
NoEstadoRelatorioCategoria *adicionarEstadoOrdenadoRelatorioCategoria(GerenciadorListaEstados *gerenciador_ref, const char *uf);
void liberarGerenciadorListaEstados(GerenciadorListaEstados *gerenciador_ref);
void imprimirRelatorioCategoria(GerenciadorListaEstados *gerenciador_estados, const char *categoria_cod);