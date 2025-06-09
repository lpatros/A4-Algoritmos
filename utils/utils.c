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
    color_printf("2. Sair.\n", COLOR_RED);
    color_printf("Escolha uma opção: ", COLOR_WHITE);
    // color_printf("2. Listar vendas do dia.\n", COLOR_RESET);
    // color_printf("3. Consultar faturamento bruto.\n", COLOR_RESET);
    // color_printf("4. Consultar quantidade de clientes.\n", COLOR_RESET);
    // color_printf("5. Consultar item mais vendido.\n", COLOR_RESET);
    // color_printf("6. Consultar item menos vendido.\n", COLOR_RESET);
    // color_printf("7. Sair.\n", COLOR_RED);
}

void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}