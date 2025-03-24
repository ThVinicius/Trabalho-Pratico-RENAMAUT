/**
 * @file gov_dev.h
 * @mainpage Módulo GovDev - Documentação Técnica
 * 
 * @details O módulo GovDev é uma biblioteca desenvolvida na linguagem de programação C para auxiliar na criação de protótipos interativos
 * para órgãos e sistemas federais. \n\n 
 * A versão disponibilizada possui apenas um subconjunto de operações e acesso restrito a dados
 * de alguns sistemas existentes. \n\n
 * 
 *
 * @section features Principais Funcionalidades:
 *
 * - Manipulação de informações sobre os estados da federação brasileira (@ref estados).
 * - Consulta a dados de fabricantes de máquinas autônomas atuantes no país (@ref fabricantes).
 * - Consulta a dados de categorias de máquinas autônomas (@ref categorias).
 * - Consulta a dados de aplicações de máquinas autônomas (@ref aplicacoes).
 * - Interfaces gráficas de usuário (GUI) baseadas em terminal ANSI para
 *       interação simplificada e visualmente organizada no terminal.
 *       Inclui menus interativos e seleção assistida por teclado (@ref interface).
 *
 * 
 * É importante destacar que esta é uma versão simplificada do módulo GovDev.
 * Este é um módulo de uso interno para prototipação e não inclui todas as funcionalidades dos sistemas reais.
 * Os dados de estados, fabricantes, categorias e aplicações são limitados,
 * servindo apenas para fins de prototipagem e demonstração das funcionalidades
 * da biblioteca. 
 *  
 * @version 1.3.0
 * @author Curso de Bacharelado em Sistemas de Informação CPTL/UFMS
 * @note Esta documentação foi gerada com o auxílio da IA assistente Qwen, 
 * disponibilizada pela Alibaba Cloud. A IA forneceu orientações e sugestões 
 * para a estruturação do código e da documentação. Todos os conteúdos foram 
 * revisados e adaptados para garantir precisão e conformidade com os objetivos propostos.
 */
#ifndef _GOV_DEV_H
#define _GOV_DEV_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

/* ============================================= 
 * ============================================= 
 * MACROS DE DEVOLUÇÃO DO MENU PRINCIPAL
 */
/**
 * @defgroup macros_opcoes Macros de Operação
 * @brief Códigos de retorno do menu principal
 * @{
 */
#define EXIT_SYSTEM 0                  /**< Opção de sair do sistema */
#define SEARCH_OPTION 1                /**< Consulta por número de registro */
#define CHANGE_STATUS_OPTION 2         /**< Inativação por número de registro */
#define RESPONSABILITY_REPORT_OPTION 3 /**< Relatório de responsabilidade */
#define CATEGORY_REPORT_OPTION 4       /**< Relatório por categoria */
/** @} */





/* ========================================================================
 * ========================================================================
 * FUNÇÕES DE INTERFACE DO USUÁRIO
 */
/**
 * @defgroup interface Interface do Usuário
 * @brief Funções para interação via terminal ANSI
 * @details Estas funções são responsáveis pela interação com o usuário através
 *    do terminal, exibindo menus, mensagens e solicitando confirmações.
 *    Utilizam sequências de escape ANSI para formatar a saída no terminal
 *    e tornar a interface mais amigável.
 * @{
 */
/**
 * @brief Exibe o menu principal e gerencia a navegação por setas
 * @return int Código correspondente à opção selecionada (ver macros de operação)
 * @note Controla todo o fluxo da interface gráfica do terminal
 */
 int main_menu(void);

/**
 * @brief Exibe uma mensagem e aguarda pressionamento da tecla ENTER
 * Esta função é útil para pausar a execução do programa em pontos específicos, 
 * permitindo que o usuário leia mensagens ou informações exibidas antes de prosseguir.
 * @param[in] msg Mensagem a ser exibida
 */
 void wait_enter(const char *msg);

/**
 * @brief Exibe uma mensagem de confirmação e aguarda a resposta do usuário
 * Esta função aceita as teclas 'S', 's', '1' para confirmar e 'N', 'n', '0' para negar.
 * @param[in] msg Mensagem de confirmação a ser exibida
 * @return int 1 para confirmação, 0 para negação
 */
 int wait_confirmation(const char *msg);
/** @} */





/* =========================================================================
 * =========================================================================
 * =========================================================================
 * =========================================================================
 * FUNÇÕES PARA MANIPULAÇÃO DE ESTADOS DA FEDERAÇÃO
 */
/**
 * @defgroup estados Gestão de Estados
 * @brief Funções para manipulação de unidades federativas
 * @details Estas funções permitem obter informações sobre os estados da federação brasileira, como siglas e nomes completos.
 * 
 * @warning Mantém um índice que itera sequencialmente sobre todos os estados brasileiros
 * em ordem alfabética crescente (Acre à Tocantins). O módulo é carregado sempre fazendo referência ao 
 * primeiro estado da lista (Acre). Ao atingir o último estado da sequencia (Tocantins), 
 * a próxima chamada de `next_state()` fará com que o índice retorne ao primeiro estado.
 * 
 * @note A ordem completa segue a lista oficial de UFs:
 * AC, AL, AP, AM, BA, CE, DF, ES, GO, MA, MT, MS, MG, PA, PB, PR, PE, PI, RJ, RN, RS, RO, RR, SC, SP, SE, TO
 * @{
 */
/**
 * @brief Obtém a sigla de um estado pelo nome completo
 * @param name Nome completo do estado (ex: "Mato Grosso do Sul")
 * @return const char* Sigla de 2 letras (ex: "MS") ou NULL se não encontrado
 */
 const char *get_state_abbr_by_name(const char *name);
 
/**
 * @brief Obtém o nome completo de um estado pela sigla
 * @param abbr Sigla de 2 letras (ex: "MS")
 * @return const char* Nome completo (ex: "Mato Grosso do Sul") ou NULL se não encontrado
 */
 const char *get_state_name_by_abbr(const char *abbr);
 
/**
 * @brief Obtém o nome completo do estado atualmente selecionado no sistema, de acordo com o índice interno de controle de estados
 * @return const char* Nome completo do estado atual (ex: "Mato Grosso do Sul") 
 */
 const char *current_state_name(void);

/**
 * @brief Obtém a sigla do estado atualmente selecionado no sistema, de acordo com o índice interno de controle de estados
 * @return const char* Sigla do estado atual (ex: "MS")
 */
const char *current_state_abbr(void);

/**
 * @brief Avança para o próximo estado na lista de estados, incrementando o índice interno de controle de estados
 * Se o índice atingir o final da lista, volta para o primeiro estado, criando um ciclo.
 */
void next_state(void);

/**
 * @brief Retrocede para o estado anterior na lista de estados, decrementando o índice interno de controle de estados
 *  Se o índice já estiver no início da lista (primeiro estado), retrocede para o último estado, completando o ciclo de navegação.
 */
void previous_state(void);

/**
 * @brief Reinicia o contador de estados interno para o início da sequência, fazendo com que o estado a ser acessado pela 
 *          função `current_state_*()` seja o primeiro estado da lista cadastrada (Acre)
 */
void reset_state_counter(void);
/** @} */





/* ======================================================================================
 * ======================================================================================
 * FUNÇÕES PARA MANIPULAÇÃO DE FABRICANTES DE MÁQUINAS AUTÔNOMAS
 */
 /**
 * @defgroup fabricantes Acesso a Fabricantes
 * @brief Operações com cadastro de fabricantes
 * @details Estas funções permitem obter informações sobre fabricantes de máquinas autônomas, como siglas, nomes completos e identificadores.
 * @{
 */
/**
 * @brief Exibe no terminal uma lista de todos os fabricantes de máquinas autônomas cadastrados, ordenados alfabeticamente pelo ID
 * @note Formato de saída: "ID SIGLA - NOME"
 */
void show_manufacturers_by_id(void);

/**
 * @brief Exibe no terminal uma lista de fabricantes de máquinas autônomas, ordenados alfabeticamente pelo nome completo
 * @note Formato de saída: "ID SIGLA - NOME"
 */
void show_manufacturers_by_name(void);

/**
 * @brief Exibe no terminal uma listagem de todos os fabricantes de máquinas autônomas, classificados e ordenados alfabeticamente pela sigla (acronym)
 * @note Formato de saída: "ID SIGLA - NOME"
 */
void show_manufacturers_by_acronym(void);

/**
 * @brief Obtém o nome completo do fabricante de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 4 letras (ex: "TESL")
 * @return const char* Nome completo do fabricante correspondente (ex: "Tesla Inc."). 
 *         Retorna `NULL` se a sigla não for encontrada na lista de fabricantes cadastrados.
 */
const char *get_manufacturer_name_by_acronym(const char *acronym);

/**
 * @brief Obtém o ID do fabricante de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 4 caracteres (ex: "APPL")
 * @return const char* ID do fabricante correspondente (ex: "98765432000123"). 
 *         Retorna `NULL` se a sigla não for encontrada.
 */
const char *get_manufacturer_id_by_acronym(const char *acronym);

/**
 * @brief Obtém a sigla (acronym) do fabricante de máquina autônoma a partir de seu ID
 * @param id ID de 14 dígitos (ex: "12345678000190")
 * @return const char* Sigla correspondente (ex: "TESL"). Retorna `NULL` se o ID não for encontrado.
 */
const char *get_manufacturer_acronym_by_id(const char *id);

/**
 * @brief Obtém o nome completo do fabricante de máquina autônoma a partir de seu ID
 * @param id ID de 14 dígitos (ex: "98765432000123")
 * @return const char* Nome do fabricante correspondente (ex: "Apple Inc."). Retorna `NULL` se o ID não for encontrado.
 */
const char *get_manufacturer_name_by_id(const char *id);

/**
 * @brief Obtém a sigla (acronym) do fabricante de máquina autônoma a partir de seu nome completo
 * @param name Nome completo do fabricante (ex: "Google LLC")
 * @return const char* Sigla correspondente (ex: "GOGL"). Retorna `NULL` se o nome não for encontrado.
 */
const char *get_manufacturer_acronym_by_name(const char *name);

/**
 * @brief Obtém o ID do fabricante de máquina autônoma a partir de seu nome completo
 * @param name Nome completo do fabricante (ex: "Microsoft Corp.")
 * @return const char* ID correspondente (ex: "23456789000167"). Retorna `NULL` se o nome não for encontrado.
 */
const char *get_manufacturer_id_by_name(const char *name);
/** @} */





/* ======================================================================================
 * ======================================================================================
 * FUNÇÕES PARA MANIPULAÇÃO DE CATEGORIAS DE MÁQUINAS AUTÔNOMAS
 */
/**
 * @defgroup categorias Acesso a Categorias
 * @brief Operações com categorias de máquinas
 * @details Estas funções permitem obter informações sobre categorias de máquinas autônomas, como siglas, nomes completos e códigos de identificação numéricos.
 * @{
 */

/**
 * @brief Interface interativa para seleção de categorias cadastradas
 * @return const char* Código de 6 dígitos da categoria selecionada
 * @note Utiliza interface gráfica com navegação por setas
 */
const char *select_category(void);

/**
 * @brief Exibe no terminal uma lista de todas as categorias de máquinas autônomas, ordenadas alfabeticamente pelo código
 * @note Formato de saída: "CÓDIGO SIGLA - NOME"
 */
void show_categories_by_code(void);

/**
 * @brief Exibe no terminal uma lista de categorias de máquinas autônomas, ordenadas alfabeticamente pelo nome completo
 * @note Formato de saída: "CÓDIGO SIGLA - NOME"
 */
void show_categories_by_name(void);

/**
 * @brief Exibe no terminal uma listagem de todas as categorias de máquinas autônomas, classificadas e ordenadas alfabeticamente pela sigla (acronym)
 * @note Formato de saída: "CÓDIGO SIGLA - NOME"
 */
void show_categories_by_acronym(void);

/**
 * @brief Obtém o nome da categoria de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 3 caracteres (ex: "DRN")
 * @return Nome completo correspondente (ex: "Drone"). Retorna `NULL` se a sigla não for encontrada
 */
const char *get_category_name_by_acronym(const char *acronym);

/**
 * @brief Obtém o código numérico da categoria de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 3 caracteres (ex: "CLN")
 * @return Código de 6 dígitos correspondente (ex: "541482"). Retorna `NULL` se a sigla não for encontrada
 */
const char *get_category_code_by_acronym(const char *acronym);

/**
 * @brief Obtém a sigla (acronym) da categoria de máquina autônoma a partir de seu código numérico
 * @param code Código de 6 dígitos (ex: "103456")
 * @return Sigla correspondente (ex: "DRN"). Retorna `NULL` se o código não for encontrado
 */
const char *get_category_acronym_by_code(const char *code);

/**
 * @brief Obtém o nome completo da categoria de máquina autônoma a partir de seu código numérico
 * @param code Código de 6 dígitos (ex: "541482")
 * @return Nome da categoria correspondente (ex: "Robô Aspirador"). Retorna `NULL` se o código não for encontrado
 */
const char *get_category_name_by_code(const char *code);

/**
 * @brief Obtém a sigla (acronym) da categoria de máquina autônoma a partir de seu nome completo
 * @param name Nome completo da categoria (ex: "Veículo Autônomo Terrestre")
 * @return Sigla correspondente (ex: "VEI"). Retorna `NULL` se o nome não for encontrado
 */
const char *get_category_acronym_by_name(const char *name);

/**
 * @brief Obtém o código numérico da categoria de máquina autônoma a partir de seu nome completo
 * @param name Nome completo da categoria (ex: "Robô de Entrega")
 * @return Código de 6 dígitos correspondente (ex: "212972"). Retorna `NULL` se o nome não for encontrado
 */
const char *get_category_code_by_name(const char *name);
/** @} */





/* ======================================================================================
 * ======================================================================================
 * FUNÇÕES PARA MANIPULAÇÃO DE APLICAÇÕES DE MÁQUINAS AUTÔNOMAS
 */
/**
 * @defgroup aplicacoes Acesso a Aplicações 
 * @brief Operações com aplicações de máquinas
 * @details Estas funções permitem obter informações sobre aplicações de máquinas autônomas, como siglas, descrições completas e códigos de identificação numéricos.
 * @{
 */
/**
 * @brief Exibe no terminal uma listagem de todas as aplicações de máquinas autônomas, classificadas e ordenadas alfabeticamente pelo código
 * @note Formato de saída: "CÓDIGO SIGLA - DESCRIÇÃO"
 */
void show_applications_sorted_by_code(void);

/**
 * @brief Exibe no terminal uma listagem de todas as aplicações de máquinas autônomas, classificadas e ordenadas alfabeticamente pela sigla
 * @note Formato de saída: "SIGLA CÓDIGO - DESCRIÇÃO"
 */
void show_applications_sorted_by_acronym(void);

/**
 * @brief Exibe no terminal uma listagem de todas as aplicações de máquinas autônomas, classificadas e ordenadas alfabeticamente pela descrição
 * @note Formato de saída: "SIGLA CÓDIGO - DESCRIÇÃO"
 */
void show_applications_sorted_by_description(void);

 /**
 * @brief Obtém a descrição detalhada da aplicação de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 3 letras (ex: "AGP")
 * @return const char* Descrição completa correspondente (ex: "Agricultura de Precisão"). Retorna `NULL` se a sigla não for encontrada
 */
const char *get_application_description_by_acronym(const char *acronym);

/**
 * @brief Obtém o código numérico da aplicação de máquina autônoma a partir de sua sigla (acronym)
 * @param acronym Sigla de 3 letras (ex: "RES")
 * @return const char* Código de 6 dígitos correspondente (ex: "202345"). Retorna `NULL` se a sigla não for encontrada
 */
const char *get_application_code_by_acronym(const char *acronym);

/**
 * @brief Obtém a sigla (acronym) da aplicação de máquina autônoma a partir de seu código numérico
 * @param code Código de 6 dígitos (ex: "101234")
 * @return const char* Sigla correspondente (ex: "AGP"). Retorna `NULL` se o código não for encontrado
 */
const char *get_application_acronym_by_code(const char *code);

/**
 * @brief Obtém a descrição detalhada da aplicação de máquina autônoma a partir de seu código numérico
 * @param code Código de 6 dígitos (ex: "202345")
 * @return const char* Descrição completa correspondente (ex: "Resgate em Emergências"). Retorna `NULL` se o código não for encontrado
 */
const char *get_application_description_by_code(const char *code);

/**
 * @brief Obtém a sigla (acronym) da aplicação de máquina autônoma a partir de sua descrição
 * @param description Descrição completa (ex: "Agricultura de Precisão")
 * @return const char* Sigla correspondente (ex: "AGP"). Retorna `NULL` se a descrição não for encontrada
 */
const char *get_application_acronym_by_description(const char *description);

/**
 * @brief Obtém o código numérico da aplicação de máquina autônoma a partir de sua descrição
 * @param description Descrição completa (ex: "Resgate em Emergências")
 * @return const char* Código de 6 dígitos correspondente (ex: "202345"). Retorna `NULL` se a descrição não for encontrada
 */
const char *get_application_code_by_description(const char *description);
/** @} */






/* ======================================================================================
 * ======================================================================================
 * FUNÇÕES PARA APLICAÇÃO DE MÁSCARAS E VALIDAÇÕES
 */
 /**
 * @defgroup mascaras Aplicação de máscaras e validações
 * @brief Operações para aplicação ou remoção de máscaras e para validação de CPF, CNPJ e RENAMAUT
 * @details Estas funções permitem formatar strings de entrada com máscaras específicas e validar CPF, CNPJ e RENAMAUT.
 * @{
 */
 /**
  * @brief Aplica máscara de formatação para CPF.
  * @param input CPF sem máscara (11 dígitos).
  * @param output Buffer para armazenar o CPF formatado.
  */
 void apply_mask_cpf(const char *input, char *output);

/**
 * @brief Aplica máscara de formatação para CNPJ.
 * @param input CNPJ sem máscara (14 dígitos).
 * @param output Buffer para armazenar o CNPJ formatado.
 */
void apply_mask_cnpj(const char *input, char *output);

/**
 * @brief Aplica máscara de formatação para RENAMAUT.
 * @param input RENAMAUT sem máscara (16 caracteres).
 * @param output Buffer para armazenar o RENAMAUT formatado.
 */
void apply_mask_renamaut(const char *input, char *output);

/**
 * @brief Remove máscara de formatação de qualquer entrada.
 * @param input String formatada com máscara.
 * @param output Buffer para armazenar a string sem máscara.
 */
void remove_mask(const char *input, char *output);

/**
* @brief Valida um CPF usando o cálculo dos dígitos verificadores.
* @param cpf CPF a ser validado (11 dígitos).
* @return int Retorna 1 se o CPF for válido, 0 caso contrário.
*/
int validate_cpf(const char *cpf);

/**
* @brief Valida um CNPJ usando o cálculo dos dígitos verificadores.
* @param cnpj CNPJ a ser validado (14 dígitos).
* @return int Retorna 1 se o CNPJ for válido, 0 caso contrário.
*/
int validate_cnpj(const char *cnpj);

/**
 * @brief Valida um RENAMAUT usando consultas às bases de dados federais.
 * @param renamaut RENAMAUT a ser validado (16 caracteres).
 * @return int Retorna 1 se o RENAMAUT for válido, 0 caso contrário.
 */
int validate_renamaut(const char *renamaut);
/** @} */


#endif /* _GOV_DEV_H */
