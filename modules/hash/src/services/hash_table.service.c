#include "hash_table.service.h"
#include <stdlib.h>
#include <stdio.h>

TabelaHash *inicializarTabelaHash()
{
    int i;
    TabelaHash *novaTabela = (TabelaHash *)malloc(sizeof(TabelaHash));
    if (novaTabela == NULL)
    {
        fprintf(stderr, "Erro: Falha ao alocar memória para a Tabela Hash.\n");
        return NULL;
    }
    for (i = 0; i < TAMANHO_TABELA_HASH; i++)
    {
        novaTabela->baldes[i] = NULL;
    }
    return novaTabela;
}

void inserirNaTabelaHash(TabelaHash *tabela, Registro maquina)
{
    int indice;
    printf("inserirNaTabelaHash 1\n");
    if (tabela == NULL)
    {
        printf("inserirNaTabelaHash 2\n");
        return;
    }
    indice = fnv1a_hash(maquina.renamaut) % TAMANHO_TABELA_HASH;
    printf("inserirNaTabelaHash 3\n");
    
    tabela->baldes[indice] = (NoAVL *)inserirAVL((EstruturaDados)tabela->baldes[indice], maquina);
    printf("inserirNaTabelaHash 4\n");
}

Registro *buscarNaTabelaHash(TabelaHash *tabela, const char *renamaut)
{
    int indice;
    if (tabela == NULL)
    {
        return NULL;
    }
    indice = fnv1a_hash(renamaut) % TAMANHO_TABELA_HASH;
    return buscarAVL((EstruturaDados)tabela->baldes[indice], renamaut);
}