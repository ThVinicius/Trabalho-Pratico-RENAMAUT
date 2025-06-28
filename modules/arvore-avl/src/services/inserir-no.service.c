#include "inserir-no.service.h"

int altura(NoAVL *N)
{
  if (N == NULL)
    return 0;
  return N->altura;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int fatorBalanceamento(NoAVL *N)
{
  if (N == NULL)
    return 0;
  return altura(N->esquerda) - altura(N->direita);
}

NoAVL *rotacaoDireita(NoAVL *y)
{
  NoAVL *x = y->esquerda;
  NoAVL *T2 = x->direita;

  /* Realiza a rotação */
  x->direita = y;
  y->esquerda = T2;

  /* Atualiza alturas */
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

  return x; /* Retorna a nova raiz */
}

NoAVL *rotacaoEsquerda(NoAVL *x)
{
  NoAVL *y = x->direita;
  NoAVL *T2 = y->esquerda;

  /* Realiza a rotação */
  y->esquerda = x;
  x->direita = T2;

  /* Atualiza alturas */
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

  return y; /* Retorna a nova raiz */
}

NoAVL *_inserirAVL(NoAVL *no, Registro maquina)
{
  int comparacao;
  int balanco;

  /* 1. Realiza a inserção normal da BST */
  if (no == NULL)
    return criarNoAVL(maquina);

  comparacao = strcmp(maquina.renamaut, no->dados.renamaut);

  if (comparacao < 0)
    no->esquerda = _inserirAVL(no->esquerda, maquina);
  else if (comparacao > 0)
    no->direita = _inserirAVL(no->direita, maquina);
  else
  {
    printf("Aviso: Máquina com registro %s já existe. Ignorando inserção.\n", maquina.renamaut);
    return no;
  }

  /* 2. Atualiza a altura do nó ancestral */
  no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

  /* 3. Obtém o fator de balanceamento deste nó ancestral para verificar o balanceamento */
  balanco = fatorBalanceamento(no);

  /* 4. Se o nó se tornou desbalanceado, então há 4 casos */

  /* Caso Esquerda-Esquerda */
  if (balanco > 1 && strcmp(maquina.renamaut, no->esquerda->dados.renamaut) < 0)
    return rotacaoDireita(no);

  /* Caso Direita-Direita */
  if (balanco < -1 && strcmp(maquina.renamaut, no->direita->dados.renamaut) > 0)
    return rotacaoEsquerda(no);

  /* Caso Esquerda-Direita */
  if (balanco > 1 && strcmp(maquina.renamaut, no->esquerda->dados.renamaut) > 0)
  {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
  }

  /* Caso Direita-Esquerda */
  if (balanco < -1 && strcmp(maquina.renamaut, no->direita->dados.renamaut) < 0)
  {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
  }

  return no; /* Retorna o ponteiro (inalterado) do nó */
}

EstruturaDados inserirAVL(EstruturaDados estrutura_dados, Registro maquina)
{
  NoAVL *raiz = (NoAVL *)estrutura_dados;
  return (EstruturaDados)_inserirAVL(raiz, maquina);
}