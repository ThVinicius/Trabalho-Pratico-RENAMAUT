#include "carregar-dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add.h"
#include "../types/registro.type.h"

void carregar_dados(Registros **lista) {
    FILE *pont_arq;
    Registro novo;
    char linha[512];
    char *token;

    pont_arq = fopen("dados.txt", "r");

    if (pont_arq == NULL) {
        printf("Erro ao abrir o arquivo dados.txt\n");
        return;
    }

    printf("Lendo dados do arquivo\n");

    while (fgets(linha, sizeof(linha), pont_arq)) {
        linha[strcspn(linha, "\n")] = '\0';

        token = strtok(linha, ",");

        if (!token) continue;
        strcpy(novo.renamaut, token);

        token = strtok(NULL, ",");
        strcpy(novo.fab, token);

        token = strtok(NULL, ",");
        strcpy(novo.mod, token);

        token = strtok(NULL, ",");
        strcpy(novo.cat, token);

        token = strtok(NULL, ",");
        strcpy(novo.apl, token);

        token = strtok(NULL, ",");
        novo.ano = atoi(token);

        token = strtok(NULL, ",");
        strcpy(novo.resp, token);

        token = strtok(NULL, ",");
        strcpy(novo.cidade, token);

        token = strtok(NULL, ",");
        strcpy(novo.uf, token);

        token = strtok(NULL, ",");
        novo.status = atoi(token);

        add_registro(lista, &novo);
    }

    fclose(pont_arq);
    printf("Dados carregados com sucesso\n");
}

