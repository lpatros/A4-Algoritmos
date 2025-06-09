#ifndef UTILS_H
#define UTILS_H

#include <time.h>

typedef enum {
    COLOR_RESET = 0,
    COLOR_BLACK = 30,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34,
    COLOR_MAGENTA = 35,
    COLOR_CYAN = 36,
    COLOR_WHITE = 37
} ColorText;

typedef struct {
    char dateStr[11];   // Formato "DD/MM/AA"
    int dia;            // Dia do mês
    int mes;            // Mês do ano
    int ano;            // Ano
} Data;

void menu();
void limparTerminal();
void limparBufferEntrada();
void color_printf(char *text, ColorText color);

#endif