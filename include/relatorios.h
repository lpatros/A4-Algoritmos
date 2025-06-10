#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "venda.h"

typedef struct {
        int codigoItem;
        char nomeItem[50];
        int quantidadeTotal;
} ProdutoVendido;

void resumoCompra(Venda vendas[], int *numVendas);
void listarVendasPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);
void exibirFaturamentoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);
void exibirQuantidadeClientesPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);
void exibirProdutoMaisVendidoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);
void exibirProdutoMenosVendidoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);

#endif