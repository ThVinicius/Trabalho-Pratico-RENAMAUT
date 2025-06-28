#include <stdio.h>
#include <string.h>
#include "../../types/no-avl.type.h"
#include "criar-no.service.h"
#include "../../types/callbacks.h"

int altura(NoAVL *N);
int max(int a, int b);
int fatorBalanceamento(NoAVL *N);
NoAVL *rotacaoDireita(NoAVL *y);
NoAVL *rotacaoEsquerda(NoAVL *x);

EstruturaDados inserirAVL(EstruturaDados estrutura_dados, Registro maquina);