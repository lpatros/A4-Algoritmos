#ifndef UTILS_H
#define UTILS_H

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
    char dateStr[11];   // Formato "DD/MM/AAAA"
    int day;            // Dia do mês
    int month;          // Mês do ano
    int year;           // Ano
} Date;

void menu();
void clearTerminal();
void clearInputBuffer();
void getCurrentDate(Date *date);
char* getConsultationDate();
void color_printf(char *text, ColorText color);

#endif
