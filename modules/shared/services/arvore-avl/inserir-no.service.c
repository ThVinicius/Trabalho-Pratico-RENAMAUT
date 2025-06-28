#include "./inserir-no.service.h"
#include <string.h> /* Para strcmp */
#include <stdio.h>  /* Para printf */
#include "../imprimir-maquina-formatada.service.h"

/* Função auxiliar para obter a altura de um nó */
int altura(NoAVL *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

/* Função auxiliar para obter o máximo de dois inteiros */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Função auxiliar para obter o fator de balanceamento de um nó */
int fatorBalanceamento(NoAVL *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}

/* Função para rotação simples à direita */
NoAVL *rotacaoDireita(NoAVL *y)
{
    printf("DEBUG: rotacaoDireita - Iniciada para no %s\n", y->dados.renamaut);
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    /* Realiza a rotação */
    x->direita = y;
    y->esquerda = T2;

    /* Atualiza alturas */
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    printf("DEBUG: rotacaoDireita - Finalizada. Nova raiz: %s\n", x->dados.renamaut);
    return x;
}

/* Função para rotação simples à esquerda */
NoAVL *rotacaoEsquerda(NoAVL *x)
{
    printf("DEBUG: rotacaoEsquerda - Iniciada para no %s\n", x->dados.renamaut);
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    /* Realiza a rotação */
    y->esquerda = x;
    x->direita = T2;

    /* Atualiza alturas */
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    printf("DEBUG: rotacaoEsquerda - Finalizada. Nova raiz: %s\n", y->dados.renamaut);
    return y;
}

/* Função de inserção recursiva para AVL */
NoAVL *_inserirAVL(NoAVL *no, Registro maquina)
{
    int comparacao;
    int balanco;

    imprimir_maquina_formatada(maquina);

    printf("DEBUG: _inserirAVL - Chamada para inserir %s. No atual: %p\n", maquina.renamaut, (void*)no);

    /* 1. Realiza a inserção normal da BST */
    if (no == NULL) {
        printf("DEBUG: _inserirAVL - No NULL, criando novo para %s\n", maquina.renamaut);
        return criarNoAVL(maquina);
    }

    printf("DEBUG: _inserirAVL - Comparando '%s' (nova) com '%s' (atual)\n", maquina.renamaut, no->dados.renamaut);
    comparacao = strcmp(maquina.renamaut, no->dados.renamaut);
    printf("DEBUG: _inserirAVL - Resultado comparacao: %d\n", comparacao);

    if (comparacao < 0) {
        printf("DEBUG: _inserirAVL - Indo para a esquerda de %s\n", no->dados.renamaut);
        no->esquerda = _inserirAVL(no->esquerda, maquina);
    } else if (comparacao > 0) {
        printf("DEBUG: _inserirAVL - Indo para a direita de %s\n", no->dados.renamaut);
        no->direita = _inserirAVL(no->direita, maquina);
    } else {
        printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
        return no;
    }

    /* 2. Atualiza a altura do nó ancestral */
    printf("DEBUG: _inserirAVL - Atualizando altura de %s\n", no->dados.renamaut);
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    /* 3. Obtém o fator de balanceamento deste nó ancestral */
    balanco = fatorBalanceamento(no);
    printf("DEBUG: _inserirAVL - Fator de balanceamento de %s: %d\n", no->dados.renamaut, balanco);

    /* 4. Casos de rotação */
    
    /* Caso Esquerda-Esquerda */
    if (balanco > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        printf("DEBUG: _inserirAVL - Caso LL acionado para %s\n", no->dados.renamaut);
        return rotacaoDireita(no);
    }

    /* Caso Esquerda-Direita */
    if (balanco > 1 && fatorBalanceamento(no->esquerda) < 0) {
        printf("DEBUG: _inserirAVL - Caso LR acionado para %s\n", no->dados.renamaut);
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    /* Caso Direita-Direita */
    if (balanco < -1 && fatorBalanceamento(no->direita) <= 0) {
        printf("DEBUG: _inserirAVL - Caso RR acionado para %s\n", no->dados.renamaut);
        return rotacaoEsquerda(no);
    }

    /* Caso Direita-Esquerda */
    if (balanco < -1 && fatorBalanceamento(no->direita) > 0) {
        printf("DEBUG: _inserirAVL - Caso RL acionado para %s\n", no->dados.renamaut);
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    printf("DEBUG: _inserirAVL - Finalizando insercao para %s\n", no->dados.renamaut);
    return no;
}

/* Wrapper para a função de inserção AVL */
EstruturaDados inserirAVL(EstruturaDados estrutura_dados, Registro maquina) {
    NoAVL *raiz = (NoAVL *)estrutura_dados;
    NoAVL *nova_raiz = _inserirAVL(raiz, maquina);
    return (EstruturaDados)nova_raiz;
}