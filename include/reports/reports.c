#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "reports.h"
#include "../../utils/utils.h"

SaleList getSalesByDay(SaleList saleList, const char *dataQuery) {
    SaleList salesByDay = {
        .numSales = 0,
        .nextClientId = 0,
        .sales = NULL
    };
    for (int i = 0; i < saleList.numSales; i++) {
        if (strcmp(saleList.sales[i].date.dateStr, dataQuery) == 0) {
            addSale(&salesByDay, saleList.sales[i]);
        }
    }
    return salesByDay;
}

int getTotalQuantitySold(SaleList saleList) {
    Date currentDate;
    int totalQuantitySold = 0;
    getCurrentDate(&currentDate);

    for (int i = 0; i < saleList.numSales; i++) {
        if (strcmp(saleList.sales[i].date.dateStr, currentDate.dateStr) == 0) {
            totalQuantitySold += saleList.sales[i].quantity;
        }
    }
    return totalQuantitySold;
}

int getTotalCustomers(SaleList saleList) {
    Date currentDate;
    int totalQuantityCustomers = 0;

    getCurrentDate(&currentDate);

    for (int i = 0; i < saleList.numSales; i++) {
        if (strcmp(saleList.sales[i].date.dateStr, currentDate.dateStr) == 0) {
            totalQuantityCustomers++;
        }
    }
    return totalQuantityCustomers;
}

void summaryPurchase(SaleList saleList) {
    int totalQuantitySold = getTotalQuantitySold(saleList);

    color_printf("------------------------------ Resumo da Compra -----------------------------\n", COLOR_WHITE);
    printf("| %10s | %4s | %-10s | %10s | %9s | %5s | %10s |\n","ID Cliente", "Item", "Nome", "Marca", "Quantidade", "Preco", "Valor Total");
    printf("| %10d | %4d | %-10s | %10s | %10d | %5.2f | %11.2f |\n",
        saleList.sales[saleList.numSales - 1].id,
        saleList.sales[saleList.numSales - 1].codeItem,
        saleList.sales[saleList.numSales - 1].nameItem,
        saleList.sales[saleList.numSales - 1].markItem,
        saleList.sales[saleList.numSales - 1].quantity,
        saleList.sales[saleList.numSales - 1].unitPrice,
        saleList.sales[saleList.numSales - 1].totalPrice
    );

    color_printf("-----------------------------------------------------------------------------\n", COLOR_WHITE);
    printf("Total de itens vendidos: %d\n", totalQuantitySold);
}

void listSaleByDay(SaleList saleList, const char *dataQuery) {
    SaleList saleOfTheDay = getSalesByDay(saleList, dataQuery);
    int totalQuantitySoldDay = getTotalQuantitySold(saleOfTheDay);

    if (saleOfTheDay.numSales == 0) {
        printf("Nenhuma venda registrada para o dia %s.\n", dataQuery);
        color_printf("---------------------------------------------------------------------------\n", COLOR_WHITE);
        return;
    }

    for (int i = 0; i < saleOfTheDay.numSales - 1; i++) {
        bool swapped_in_pass = false;
        for (int j = 0; j < saleOfTheDay.numSales - 1 - i; j++) {
            if (saleOfTheDay.sales[j].totalPrice < saleOfTheDay.sales[j+1].totalPrice) {
                const Sale temp = saleOfTheDay.sales[j];
                saleOfTheDay.sales[j] = saleOfTheDay.sales[j+1];
                saleOfTheDay.sales[j+1] = temp;
                swapped_in_pass = true;
            }
        }
        if (!swapped_in_pass) {
            break;
        }
    }

    char title_str[120];
    sprintf(title_str, "----------- sale do Dia (%s) - Ordenadas por Faturamento -----------", dataQuery);
    color_printf(title_str, COLOR_WHITE);
    printf("\n");

    printf("| %10s | %4s | %-10s | %-20s | %10s | %5s | %11s |\n",
        "ID Cliente", "Item", "Nome", "Marca", "Quantidade", "Preco", "Valor Total");
    color_printf("|---------------------------------------------------------------------------|\n", COLOR_WHITE);

    for (int i = 0; i < saleOfTheDay.numSales; i++) {
        printf("| %10d | %4d | %-10s | %-20s | %10d | %5.2f | %11.2f |\n",
            saleOfTheDay.sales[i].id,
            saleOfTheDay.sales[i].codeItem,
            saleOfTheDay.sales[i].nameItem,
            saleOfTheDay.sales[i].markItem,
            saleOfTheDay.sales[i].quantity,
            saleOfTheDay.sales[i].unitPrice,
            saleOfTheDay.sales[i].totalPrice
        );
    }
    color_printf("-----------------------------------------------------------------------------\n", COLOR_WHITE);
    printf("Total de itens vendidos no dia %s: %d\n", dataQuery, totalQuantitySoldDay);
    color_printf("-----------------------------------------------------------------------------\n", COLOR_WHITE);
}

void displayBillingPerDay(SaleList saleList, const char *dataQuery) {
    float totalRevenue = 0.0;

    SaleList saleOfTheDay = getSalesByDay(saleList, dataQuery);

    for (int i = 0; i < saleOfTheDay.numSales; i++) {
        if (strcmp(saleOfTheDay.sales[i].date.dateStr, dataQuery) == 0) {
            totalRevenue += saleOfTheDay.sales[i].totalPrice;
        }
    }

    color_printf("------ Faturamento do Dia ------\n", COLOR_WHITE);
    printf("| %21s %.2f |\n", "Faturamento Total: R$", totalRevenue);
    color_printf("--------------------------------\n", COLOR_WHITE);
}

void displayNumberOfCustomersPerDay(SaleList saleList, const char *dataQuery) {
    int totalCustomers = getTotalCustomers(saleList);

    printf("----- Clientes Atendidos no dia %s -----\n", dataQuery);
    printf("| %-41s %d |\n", "Quantidade de Clientes: ", totalCustomers);
    color_printf("------------------------------------------------\n", COLOR_WHITE);
}

void displayBestsellingProductPerDay(SaleList saleList, const char *dataQuery) {
    SaleList saleOfTheDay = getSalesByDay(saleList, dataQuery);
    ProductSold products[saleOfTheDay.numSales];
    int numProducts = 0;

    // Somar quantidades por código de item
    for (int i = 0; i < saleOfTheDay.numSales; i++) {
        int found = 0;

        // Procurar se o código já existe no array
        for (int j = 0; j < numProducts; j++) {
            if (products[j].codeItem == saleOfTheDay.sales[i].codeItem) {
                products[j].totalQuantity += saleOfTheDay.sales[i].quantity;
                found = 1;
                break;
            }
        }
        // Se não found, adicionar novo produto
        if (!found) {
            products[numProducts].codeItem = saleOfTheDay.sales[i].codeItem;
            strcpy(products[numProducts].nameItem, saleOfTheDay.sales[i].nameItem);
            products[numProducts].totalQuantity = saleOfTheDay.sales[i].quantity;
            numProducts++;
        }
    }

    // Encontrar o produto com maior quantidade
    int largestQuantity = -1;
    int indexLargest = -1;

    for (int i = 0; i < numProducts; i++) {
        if (products[i].totalQuantity> largestQuantity) {
            largestQuantity = products[i].totalQuantity;
            indexLargest = i;
        }
    }

    // Exibir resultado
    if (indexLargest != -1) {
        printf("\n------- Produto mais vendido do dia %s -----\n", dataQuery);
        printf("| %4s | %-20s | %s |\n", "Item", "Nome", "Quantidade Vendida");
        printf("| %4d | %-20s | %18d |\n",
            products[indexLargest].codeItem,
            products[indexLargest].nameItem,
            products[indexLargest].totalQuantity);
    } else {
        printf("Nenhuma venda encontrada para o dia %s.\n", dataQuery);
    }
    color_printf("----------------------------------------------------\n", COLOR_WHITE);
}

void displayProductLeastSoldPerDay(SaleList saleList, const char *dataQuery) {
    SaleList saleOfTheDay = getSalesByDay(saleList, dataQuery);
    ProductSold products[saleOfTheDay.numSales];
    int numProducts = 0;

    // Somar quantidades por código de item
    for (int i = 0; i < saleOfTheDay.numSales; i++) {
        int found = 0;

        // Procurar se o código já existe no array
        for (int j = 0; j < numProducts; j++) {
            if (products[j].codeItem == saleOfTheDay.sales[i].codeItem) {
                products[j].totalQuantity += saleOfTheDay.sales[i].quantity;
                found = 1;
                break;
            }
        }
        // Se não found, adicionar novo produto
        if (!found) {
            products[numProducts].codeItem = saleOfTheDay.sales[i].codeItem;
            strcpy(products[numProducts].nameItem, saleOfTheDay.sales[i].nameItem);
            products[numProducts].totalQuantity = saleOfTheDay.sales[i].quantity;
            numProducts++;
        }
    }

    // Encontrar o produto com menor quantidade
    int smallestQuantity = products[0].totalQuantity; // Garantir que qualquer quantidade será menor
    int indexSmallest = -1;

    for (int i = 0; i < numProducts; i++) {
        if (products[i].totalQuantity <= smallestQuantity) {
            smallestQuantity = products[i].totalQuantity;
            indexSmallest = i;
        }
    }

    // Exibir resultado
    if (indexSmallest != -1) {
        printf("\n------ Produto menos vendido do dia %s -----\n", dataQuery);
        printf("| %4s | %-20s | %s |\n", "Item", "Nome", "Quantidade Vendida");
        printf("| %4d | %-20s | %18d |\n",
            products[indexSmallest].codeItem,
            products[indexSmallest].nameItem,
            products[indexSmallest].totalQuantity);
    } else {
        printf("Nenhuma venda encontrada para o dia %s.\n", dataQuery);
    }
    color_printf("----------------------------------------------------\n", COLOR_WHITE);
}