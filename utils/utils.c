#include "../include/utils.h"
#include <stdio.h>

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}