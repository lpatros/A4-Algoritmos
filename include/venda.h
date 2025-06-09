#ifndef VENDA_H
#define VENDA_H

#define MAX_VENDAS 1000
#define ARQUIVO "data/loja_roupa.txt"
#include "utils.h"

typedef struct {
    int idCliente;
    int codigoItem;
    char nomeItem[50];
    char marcaItem[50];
    int quantidade;
    float precoUnitario;
    float precoTotal;
    Data data;
} Venda;

void adicionarVenda(Venda vendas[], Venda *novaVenda, int *numVendas, int *proximoIdCliente);
void salvarVendas(Venda vendas[], int *numVendas);
int carregarVendas(Venda vendas[]);

#endif
