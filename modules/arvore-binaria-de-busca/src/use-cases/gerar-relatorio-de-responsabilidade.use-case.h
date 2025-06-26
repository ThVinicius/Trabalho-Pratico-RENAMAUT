#include "../services/coletar-maquinas-por-status-e-responsavel.service.h"
#include "../../../shared/services/inicializar-gerenciador-lista.service.h"
#include "../../../shared/services/relatorio-de-responsabilidade/imprimir-relatorio-de-responsabilidade.service.h"
#include "../../../shared/services/liberar-gerenciador-lista.service.h"

void gerar_relatorio_de_responsabilidade(NoABB *raiz, const char *cpf_cnpj);