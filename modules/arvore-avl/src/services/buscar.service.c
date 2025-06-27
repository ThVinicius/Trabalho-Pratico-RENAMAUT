#include "./buscar.service.h"

Registro *buscarAVL(EstruturaDados estrutura_dados, const char *numero_registro)
{
  NoAVL *no = (NoAVL *)estrutura_dados;
  int comparacao;

  while (no != NULL)
  {
    comparacao = strcmp(numero_registro, no->dados.renamaut);

    if (comparacao == 0)
    {
      return &(no->dados);
    }
    else if (comparacao < 0)
    {
      no = no->esquerda;
    }
    else
    {
      no = no->direita;
    }
  }

  return NULL;
}