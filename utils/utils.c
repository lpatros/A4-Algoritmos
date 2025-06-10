#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void color_printf(char *text, ColorText color)
{
    printf("\033[%dm%s\033[0m", color, text);
}

void menu() {
    color_printf("\n----- Loja de Roupas -----\n", COLOR_GREEN);
    color_printf("1. Registrar venda.\n", COLOR_RESET);
    color_printf("2. Listar vendas do dia.\n", COLOR_RESET);
    color_printf("3. Consultar faturamento bruto.\n", COLOR_RESET);
    color_printf("4. Consultar quantidade de clientes que realizaram compras.\n", COLOR_RESET);
    color_printf("5. Consultar item mais vendido.\n", COLOR_RESET);
    color_printf("6. Consultar item menos vendido.\n", COLOR_RESET);
    color_printf("7. Sair.\n", COLOR_RED);
    color_printf("Escolha uma opção: ", COLOR_WHITE);
}

void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pegarDataAtual(Data *data) {
    // Obter a data atual
    time_t t = time(NULL);
    struct tm *data_atual_info = localtime(&t);

    if (data == NULL || data_atual_info == NULL) {
        color_printf("Erro ao obter a data atual.\n", COLOR_RED);
        return;
    }

    // Preencher a estrutura Data com a data atual
    data->dia = data_atual_info->tm_mday;
    data->mes = data_atual_info->tm_mon + 1;     // tm_mon é 0-11 (janeiro = 0)
    data->ano = data_atual_info->tm_year + 1900; // tm_year é o número de anos desde 1900
    // Formata a data para o formato "DD/MM/AAAA"
    sprintf(data->dateStr, "%02d/%02d/%04d", data->dia, data->mes, data->ano);
}