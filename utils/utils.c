#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu() {
    color_printf("\n----- Loja de Roupas -----\n", COLOR_GREEN);
    color_printf("1. Registrar venda.\n", COLOR_RESET);
    color_printf("2. Listar vendas do dia.\n", COLOR_RESET);
    color_printf("3. Consultar faturamento bruto.\n", COLOR_RESET);
    color_printf("4. Consultar quantidade de clientes que realizaram compras.\n", COLOR_RESET);
    color_printf("5. Consultar item mais vendido.\n", COLOR_RESET);
    color_printf("6. Consultar item menos vendido.\n", COLOR_RESET);
    color_printf("7. Sair.\n", COLOR_RED);
    color_printf("Escolha uma opcao: ", COLOR_WHITE);
}

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getCurrentDate(Date *date) {
    // Obter a date atual
    const time_t t = time(NULL);
    const struct tm *current_date_info = localtime(&t);

    if (date == NULL || current_date_info == NULL) {
        color_printf("Erro ao obter a date atual.\n", COLOR_RED);
        return;
    }

    // Preencher a estrutura date com a date atual
    date->day = current_date_info->tm_mday;
    date->month = current_date_info->tm_mon + 1;     // tm_mon é 0-11 (janeiro = 0)
    date->year = current_date_info->tm_year + 1900; // tm_year é o número de anos desde 1900
    // Formata a date para o formato "DD/MM/AAAA"
    sprintf(date->dateStr, "%02d/%02d/%04d", date->day, date->month, date->year);
}

char* getConsultationDate() {
    static char consultationDate[11];

    printf("Insira a data para consultar o faturamento (dd/mm/yyyy): ");
    fgets(consultationDate, sizeof(consultationDate), stdin);
    consultationDate[strcspn(consultationDate, "\n")] = 0;

    return consultationDate;
}

void color_printf(char *text, const ColorText color) {
    printf("\033[%dm%s\033[0m", color, text);
}
