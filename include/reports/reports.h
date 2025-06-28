#ifndef REPORTS_H
#define REPORTS_H

#include "../sale/sale.h"

typedef struct {
        int codeItem;
        char nameItem[50];
        int totalQuantity;
} ProductSold;

SaleList getSalesByDay(SaleList saleList, const char *dataQuery);
int getTotalQuantitySold(SaleList saleList, const char *dataQuery);
void summaryPurchase(SaleList saleList);
void listSaleByDay(SaleList saleList, const char *dataQuery);
void displayBillingPerDay(SaleList saleList, const char *dataQuery);
void displayNumberOfCustomersPerDay(SaleList saleList, const char *dataQuery);
void displayBestsellingProductPerDay(SaleList saleList, const char *dataQuery);
void displayProductLeastSoldPerDay(SaleList saleList, const char *dataQuery);

#endif