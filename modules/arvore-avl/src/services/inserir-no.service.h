#include <stdio.h>
#include <string.h>
#include "../types/no.type.h"
#include "criar-no.service.h"
#include "../../../shared/types/callbacks.h"

int altura(NoAVL *N);
int max(int a, int b);
int fatorBalanceamento(NoAVL *N);
NoAVL *rotacaoDireita(NoAVL *y);
NoAVL *rotacaoEsquerda(NoAVL *x);

EstruturaDados inserirAVL(EstruturaDados estrutura_dados, Registro maquina);