#include "gerenciador-lista-estado.service.h"
#include "../adicionar-registro-na-lista.service.h"
#include "../liberar-gerenciador-lista.service.h"
#include "../imprimir-lista-registro.service.h"
#include "../imprimir-maquina-formatada.service.h"
#include "../../../../libs/gov_dev/gov_dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_normalize_state_name_for_comparison(const char *input_name, char *output_buffer)
{
  int i = 0, j = 0;
  unsigned char current_char_byte;

  if (input_name == NULL || output_buffer == NULL)
  {
    if (output_buffer != NULL)
      output_buffer[0] = '\0';
    return output_buffer;
  }

  while (input_name[i] != '\0' && j < 50)
  {
    current_char_byte = (unsigned char)input_name[i];

    /* Tenta identificar caracteres acentuados comuns em UTF-8 (sequências que começam com 0xC3) */
    if (current_char_byte == 0xC3)
    {
      if (input_name[i + 1] != '\0')
      {
        unsigned char next_byte = (unsigned char)input_name[i + 1];
        char normalized_char = 0;

        switch (next_byte)
        {
        case 0x81: /* Á */
        case 0xA1: /* á */
        case 0x80: /* À */
        case 0xA0: /* à */
        case 0x82: /* Â */
        case 0xA2: /* â */
        case 0x83: /* Ã */
        case 0xA3: /* ã */
        case 0x84: /* Ä */
        case 0xA4: /* ä */
          normalized_char = 'A';
          break;
        case 0x89: /* É */
        case 0xA9: /* é */
        case 0x88: /* È */
        case 0xA8: /* è */
        case 0x8A: /* Ê */
        case 0xAA: /* ê */
          normalized_char = 'E';
          break;
        case 0x8D: /* Í */
        case 0xAD: /* í */
        case 0x8C: /* Ì */
        case 0xAC: /* ì */
          normalized_char = 'I';
          break;
        case 0x93: /* Ó */
        case 0xB3: /* ó */
        case 0x92: /* Ò */
        case 0xB2: /* ò */
        case 0x94: /* Ô */
        case 0xB4: /* ô */
        case 0x95: /* Õ */
        case 0xB5: /* õ */
        case 0x96: /* Ö */
        case 0xB6: /* ö */
          normalized_char = 'O';
          break;
        case 0x9A: /* Ú */
        case 0xBA: /* ú */
        case 0x99: /* Ù */
        case 0xB9: /* ù */
          normalized_char = 'U';
          break;
        case 0x87: /* Ç */
        case 0xA7: /* ç */
          normalized_char = 'C';
          break;
        default:
          /* Se for 0xC3 mas não for um dos caracteres acentuados esperados,
             trata como bytes literais e avança 2 posições. */
          output_buffer[j++] = (char)current_char_byte;
          if (j < 50)
            output_buffer[j++] = (char)next_byte;
          i += 2;
          continue;
        }

        output_buffer[j++] = normalized_char;
        i += 2;
      }
      else
      {
        /* Se 0xC3 for o último byte da string (string malformada), adiciona como está */
        output_buffer[j++] = (char)current_char_byte;
        i++;
      }
    }
    else
    {
      /* Para caracteres ASCII (não-acentuados) */
      /* Converte para maiúscula se for letra minúscula */
      if (current_char_byte >= 'a' && current_char_byte <= 'z')
      {
        current_char_byte = current_char_byte - 32;
      }
      output_buffer[j++] = (char)current_char_byte;
      i++;
    }
  }
  output_buffer[j] = '\0';
  return output_buffer;
}

int _compare_normalized_state_names(const char *uf1_abbr, const char *uf2_abbr)
{
  char name1_normalized[51];
  char name2_normalized[51];

  const char *name1_original = get_state_name_by_abbr(uf1_abbr);
  const char *name2_original = get_state_name_by_abbr(uf2_abbr);

  if (name1_original == NULL || name2_original == NULL)
  {
    /* Se o nome completo não for encontrado, compara pelas siglas como fallback */
    return strcmp(uf1_abbr, uf2_abbr);
  }

  _normalize_state_name_for_comparison(name1_original, name1_normalized);
  _normalize_state_name_for_comparison(name2_original, name2_normalized);

  return strcmp(name1_normalized, name2_normalized);
}

GerenciadorListaEstados *inicializarGerenciadorListaEstados()
{
  GerenciadorListaEstados *gerenciador = (GerenciadorListaEstados *)malloc(sizeof(GerenciadorListaEstados));
  if (gerenciador == NULL)
  {
    return NULL;
  }
  gerenciador->head = NULL;
  gerenciador->tail = NULL;
  return gerenciador;
}

NoEstadoRelatorioCategoria *criarNoEstadoRelatorioCategoria(const char *uf)
{
  NoEstadoRelatorioCategoria *novoNo = (NoEstadoRelatorioCategoria *)malloc(sizeof(NoEstadoRelatorioCategoria));
  if (novoNo == NULL)
  {
    return NULL;
  }

  strncpy(novoNo->uf, uf, sizeof(novoNo->uf) - 1);
  novoNo->uf[sizeof(novoNo->uf) - 1] = '\0';

  novoNo->maquinas_no_estado.head = NULL;
  novoNo->maquinas_no_estado.tail = NULL;

  novoNo->prox = NULL;
  return novoNo;
}

NoEstadoRelatorioCategoria *adicionarEstadoOrdenadoRelatorioCategoria(GerenciadorListaEstados *gerenciador_ref, const char *uf)
{
  NoEstadoRelatorioCategoria *novoNo, *atual, *anterior = NULL;

  atual = gerenciador_ref->head;
  while (atual != NULL)
  {
    if (strcmp(atual->uf, uf) == 0)
    {
      return atual;
    }
    atual = atual->prox;
  }

  novoNo = criarNoEstadoRelatorioCategoria(uf);
  if (novoNo == NULL)
  {
    return NULL;
  }

  atual = gerenciador_ref->head;
  while (atual != NULL && strcmp(uf, atual->uf) > 0)
  {
    anterior = atual;
    atual = atual->prox;
  }

  if (anterior == NULL)
  {
    novoNo->prox = gerenciador_ref->head;
    gerenciador_ref->head = novoNo;
  }
  else
  {
    novoNo->prox = atual;
    anterior->prox = novoNo;
  }

  if (novoNo->prox == NULL)
  {
    gerenciador_ref->tail = novoNo;
  }
  return novoNo;
}

void liberarGerenciadorListaEstados(GerenciadorListaEstados *gerenciador_ref)
{
  NoEstadoRelatorioCategoria *atual_estado;
  NoEstadoRelatorioCategoria *proximo_estado;

  if (gerenciador_ref == NULL)
    return;

  atual_estado = gerenciador_ref->head;

  while (atual_estado != NULL)
  {
    proximo_estado = atual_estado->prox;

    liberar_lista_registro(&(atual_estado->maquinas_no_estado));

    free(atual_estado);
    atual_estado = proximo_estado;
  }
  gerenciador_ref->head = NULL;
  gerenciador_ref->tail = NULL;
}