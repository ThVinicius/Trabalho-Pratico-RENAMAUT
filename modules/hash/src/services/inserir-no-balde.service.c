#include "inserir-no-balde.service.h"

void inserirNoBaldeHash(GerenciadorListaRegistro *gerenciador_balde, Registro maquina)
{
  Registro *maquina_existente;

  if (gerenciador_balde == NULL)
  {
    printf("Erro: Gerenciador de balde nulo ao tentar inserir %s.\n", maquina.renamaut);
    return;
  }

  /* Primeiro, verifica se a máquina já existe neste balde usando a função de busca da lista. */
  maquina_existente = buscar_na_lista_encadeada((EstruturaDados)gerenciador_balde->head, maquina.renamaut);

  if (maquina_existente != NULL)
  {
    printf("Aviso: Máquina com registro %s já existe no balde hash. Ignorando inserção.\n", maquina.renamaut);
    return;
  }

  /* Se não é duplicata, adiciona o registro na lista do balde. */
  adicionar_registro_na_lista(gerenciador_balde, maquina);
}