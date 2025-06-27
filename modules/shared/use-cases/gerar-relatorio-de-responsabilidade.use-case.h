#include "../services/inicializar-gerenciador-lista.service.h"
#include "../services/relatorio-de-responsabilidade/imprimir-relatorio-de-responsabilidade.service.h"
#include "../services/liberar-gerenciador-lista.service.h"
#include "../types/callbacks.h"

void gerar_relatorio_de_responsabilidade(EstruturaDados estrutura_dados, const char *cpf_cnpj, ColetarMaquinasPorStatusEResponsavelCallback coletar_fn);