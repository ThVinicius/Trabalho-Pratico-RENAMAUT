#include "hash_table.service.h"
#include <stdlib.h>
#include <stdio.h>

TabelaHash *inicializarTabelaHash()
{
    int i, j;
    TabelaHash *novaTabela = (TabelaHash *)malloc(sizeof(TabelaHash));
    if (novaTabela == NULL)
    {
        return NULL;
    }
    for (i = 0; i < TAMANHO_TABELA_HASH; i++)
    {
        novaTabela->baldes[i] = inicializarGerenciadorLista();
        if (novaTabela->baldes[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                liberar_lista_registro(novaTabela->baldes[j]);
                free(novaTabela->baldes[j]);
            }
            free(novaTabela);
            return NULL;
        }
    }
    return novaTabela;
}

void inserirNaTabelaHash(TabelaHash *tabela, Registro maquina)
{
    int indice;
    if (tabela == NULL)
    {
        return;
    }
    indice = fnv1a_hash(maquina.renamaut) % TAMANHO_TABELA_HASH;
    if (indice < 0)
    {
        indice += TAMANHO_TABELA_HASH;
    }

    tabela->baldes[indice]->head = (ListaRegistro *)inserir_na_lista_encadeada_ordenada(
        (EstruturaDados)tabela->baldes[indice]->head, maquina);

    if (tabela->baldes[indice]->head != NULL)
    {
        ListaRegistro *current_node = tabela->baldes[indice]->head;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        tabela->baldes[indice]->tail = current_node;
    }
    else
    {
        tabela->baldes[indice]->tail = NULL;
    }
}

Registro *buscarNaTabelaHash(TabelaHash *tabela, const char *renamaut)
{
    int indice;
    if (tabela == NULL)
    {
        return NULL;
    }
    indice = fnv1a_hash(renamaut) % TAMANHO_TABELA_HASH;
    if (indice < 0)
    { /* Garante que o índice seja não-negativo */
        indice += TAMANHO_TABELA_HASH;
    }
    /* Busca na lista encadeada do balde correspondente */
    return buscar_na_lista_encadeada((EstruturaDados)tabela->baldes[indice]->head, renamaut);
}