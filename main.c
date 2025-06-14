#include <stdio.h>
#include <string.h>
#include "include/sale/sale.h"
#include "utils/utils.h"
#include "include/reports/reports.h"

void main() {
    Date currentDate;
    getCurrentDate(&currentDate);
    char* consultationDate;

    Sale newSale = {
        .id = 0,
        .codeItem = 0,
        .nameItem = "",
        .markItem = "",
        .quantity = 0,
        .unitPrice = 0.0f,
        .totalPrice = 0.0f,
        .date = currentDate
    };

    SaleList saleList = loadSales();

    int isRunning = 1;

    while (isRunning) {
        menu();

        int option;
        scanf("%d", &option);
        clearInputBuffer();

        clearTerminal();

        if (option < 1 || option > 7) {
            color_printf("Opcao invalida.\n", COLOR_RED);
            continue;
        }

        if (option == 1) {
            newSale.id = saleList.nextClientId;

            printf("--- Registrar Nova Venda ---\n");
            printf("Digite o código do item: ");
            scanf("%d", &newSale.codeItem);
            clearInputBuffer();

            printf("Digite o nome do item: ");
            fgets(newSale.nameItem, sizeof(newSale.nameItem), stdin);
            newSale.nameItem[strcspn(newSale.nameItem, "\n")] = 0;

            printf("Digite a marca do item: ");
            fgets(newSale.markItem, sizeof(newSale.markItem), stdin);
            newSale.markItem[strcspn(newSale.markItem, "\n")] = 0;

            printf("Digite a quantidade: ");
            scanf("%d", &newSale.quantity);
            clearInputBuffer();

            printf("Digite o preço unitário: ");
            scanf("%f", &newSale.unitPrice);
            clearInputBuffer();

            saveSale(&saleList, newSale);
            summaryPurchase(saleList);
        }

        if (option == 7) {
            color_printf("Saindo...\n", COLOR_YELLOW);
            return;
        }

        consultationDate = getConsultationDate();

        switch (option) {
            case 2:
                listSaleByDay(saleList, consultationDate);
                break;
            case 3:
                displayBillingPerDay(saleList, consultationDate);
                break;
            case 4:
                displayNumberOfCustomersPerDay(saleList, consultationDate);
                break;
            case 5:
                displayBestsellingProductPerDay(saleList, consultationDate);
                break;
            case 6:
                displayProductLeastSoldPerDay(saleList, consultationDate);
                break;
        }
    }
}