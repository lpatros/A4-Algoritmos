#ifndef SALE_H
#define SALE_H
#define FILENAME "data/loja_roupa.txt"
#include "../../utils/utils.h"

typedef struct {
    int id;
    int codeItem;
    char nameItem[50];
    char markItem[50];
    int quantity;
    float unitPrice;
    float totalPrice;
    Date date;
} Sale;

typedef struct {
    int numSales;
    int nextClientId;
    Sale *sales;
} SaleList;

void addSale(SaleList *saleList, Sale sale);
void saveSale(SaleList *saleList, Sale sale);
SaleList loadSales();

#endif