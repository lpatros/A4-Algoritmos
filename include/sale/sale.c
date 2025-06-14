#include "sale.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static float calculateTotalPrice(const int quantity, const float unitPrice) {
    float total = quantity * unitPrice;
    if (quantity >= 3) {
        total *= 0.90;
    }
    return total;
}

void addSale(SaleList *saleList, const Sale sale) {
    saleList->sales = realloc(saleList->sales, sizeof(Sale) * (saleList->numSales + 1));

    if (saleList->sales == NULL) {
        printf("Erro ao alocar memória para as vendas.\n");
        return;
    }

    saleList->nextClientId = saleList->sales->id + 1;
    saleList->sales[saleList->numSales++] = sale;
}

void saveSale(SaleList *saleList, Sale sale) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sale.totalPrice = calculateTotalPrice(sale.quantity, sale.unitPrice);

    fprintf(file, "%s %d %d %s %s %d %.2f %.2f\n",
        sale.date.dateStr,
        sale.id,
        sale.codeItem,
        sale.nameItem,
        sale.markItem,
        sale.quantity,
        sale.unitPrice,
        sale.totalPrice
    );

    addSale(saleList, sale);
    fclose(file);
}

SaleList loadSales() {
    FILE *file = fopen(FILENAME, "r");
    SaleList salesList = {
        .numSales = 0,
        .nextClientId = 0,
        .sales = NULL
    };

    if (file == NULL) {
        return salesList;
    }

    Sale sale;
    while (
        fscanf(
            file,
            "%10s %d %d %49[^ ] %49[^ ] %d %f %f\n",
            sale.date.dateStr,
            &sale.id,
            &sale.codeItem,
            sale.nameItem,
            sale.markItem,
            &sale.quantity,
            &sale.unitPrice,
            &sale.totalPrice) == 8
        ) {
        sscanf(
            sale.date.dateStr, "%d/%d/%d",
            &sale.date.day,
            &sale.date.month,
            &sale.date.year
        );

        addSale(&salesList, sale);
    }
    fclose(file);
    return salesList;
}