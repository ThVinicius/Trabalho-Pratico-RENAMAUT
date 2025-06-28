#include <time.h>
#include "../../shared/services/converter-arquivo.h"
#include "../../shared/types/callbacks.h"
#include "types/hash_table.type.h"
#include "services/hash_table.service.h"
#include "services/resetar-hash.service.h"
#include "services/coletar-maquinas-por-responsavel-e-status.service.h"
#include "services/coletar-maquinas-por-categoria-e-estado.service.h"
#include "../../shared/interfaces/exibir-interface.h"
#include "../../../libs/gov_dev/gov_dev.h"

void *inserir_wrapper_hash(void *tabela_ptr, Registro registro)
{
    TabelaHash *tabela = (TabelaHash *)tabela_ptr;
    inserirNaTabelaHash(tabela, registro);
    return (void *)tabela;
}

Registro *buscar_wrapper_hash(void *tabela_ptr, const char *numero_registro)
{
    TabelaHash *tabela = (TabelaHash *)tabela_ptr;
    return buscarNaTabelaHash(tabela, numero_registro);
}

int main(int argc, char *argv[])
{
    clock_t inicio, fim;
    double tempo_para_insercao;
    TabelaHash *tabela_hash = NULL;

    tabela_hash = inicializarTabelaHash();
    if (tabela_hash == NULL)
    {
        return 1;
    }

    inicio = clock();
    converter_arquivo((void **)&tabela_hash, argc, argv, inserir_wrapper_hash);
    fim = clock();

    tempo_para_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de CPU gasto na inserção dos dados dos arquivos (Hash com Lista Encadeada): %.6f segundos\n", tempo_para_insercao);

    wait_enter("Aperte enter para inicializar o programa");

    exibir_interface(
        (EstruturaDados)tabela_hash,
        (BuscarCallback)buscar_wrapper_hash,
        (ColetarMaquinasPorStatusEResponsavelCallback)coletar_maquinas_por_responsavel_e_status_hash,
        (ColetarMaquinasPorCategoriaEEstadoCallback)coletar_maquinas_por_categoria_e_estado_hash);

    limparTabelaHash(tabela_hash);
    return 0;
}