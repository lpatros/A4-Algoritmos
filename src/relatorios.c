#include "../include/relatorios.h"
#include "../include/utils.h" 
#include <stdio.h>
#include <string.h>
// #include <stdlib.h> // Para qsort
#include <limits.h>

void resumoCompra(Venda vendas[], int *numVendas) {
    color_printf("------------------------------ Resumo da Compra -----------------------------\n", COLOR_WHITE);
    printf("| %10s | %4s | %-10s | %5s | %9s | %5s | %10s |\n","ID Cliente", "Item", "Nome", "Marca", "Quantidade", "Preco", "Valor Total");
    printf("| %10d | %4d | %-10s | %5s | %10d | %5.2f | %11.2f |\n",
        vendas[*numVendas - 1].idCliente,
        vendas[*numVendas - 1].codigoItem,
        vendas[*numVendas - 1].nomeItem,
        vendas[*numVendas - 1].marcaItem,
        vendas[*numVendas - 1].quantidade,
        vendas[*numVendas - 1].precoUnitario,
        vendas[*numVendas - 1].precoTotal
    );
    color_printf("-----------------------------------------------------------------------------\n", COLOR_WHITE);
}

// TODO: Implementar a listagem de vendas em ordem descrescente de faturamento
void listarVendasPorDia(Venda vendas[], int *numVendas, const char *dataConsulta);

void exibirFaturamentoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta) {
    float faturamentoTotal = 0.0;

    for (int i = 0; i < *numVendas; i++) {
        if (strcmp(vendas[i].data.dateStr, dataConsulta) == 0) {
            faturamentoTotal += vendas[i].precoTotal;
        }
    }

    color_printf("------ Faturamento do Dia ------\n", COLOR_WHITE);
    printf("| %21s %.2f |\n", "Faturamento Total: R$", faturamentoTotal);
    color_printf("--------------------------------\n", COLOR_WHITE);
}

void exibirQuantidadeClientesPorDia(Venda vendas[], int *numVendas, const char *dataConsulta) {
    int quantidadeClientes = 0;

    for (int i = 0; i < *numVendas; i++) {
        if (strcmp(vendas[i].data.dateStr, dataConsulta) == 0) {
            quantidadeClientes++;
        }
    }

    printf("----- Clientes Atendidos no dia %s -----\n", vendas[*numVendas - 1].data.dateStr);
    printf("| %-41s %d |\n", "Quantidade de Clientes: ", quantidadeClientes);
    color_printf("------------------------------------------------\n", COLOR_WHITE);
}

void exibirProdutoMaisVendidoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta) {
    ProdutoVendido produtos[100];
    int numProdutos = 0;

    if (*numVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        color_printf("----------------------------------------------------------\n", COLOR_WHITE);
        return;
    }

    // Somar quantidades por código de item
    for (int i = 0; i < *numVendas; i++) {
        if (strcmp(vendas[i].data.dateStr, dataConsulta) != 0) continue;

        int encontrado = 0;
        
        // Procurar se o código já existe no array
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].codigoItem == vendas[i].codigoItem) {
                produtos[j].quantidadeTotal += vendas[i].quantidade;
                encontrado = 1;
                break;
            }
        }
        // Se não encontrado, adicionar novo produto
        if (!encontrado) {
            produtos[numProdutos].codigoItem = vendas[i].codigoItem;
            strcpy(produtos[numProdutos].nomeItem, vendas[i].nomeItem);
            produtos[numProdutos].quantidadeTotal = vendas[i].quantidade;
            numProdutos++;
        }
    }

    // Encontrar o produto com maior quantidade
    int maiorQuantidade = -1;
    int indiceMaior = -1;

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].quantidadeTotal > maiorQuantidade) {
            maiorQuantidade = produtos[i].quantidadeTotal;
            indiceMaior = i;
        }
    }

    // Exibir resultado
    if (indiceMaior != -1) {
        printf("\n------- Produto mais vendido do dia %s -----\n", dataConsulta);
        printf("| %4s | %-20s | %s |\n", "Item", "Nome", "Quantidade Vendida");
        printf("| %4d | %-20s | %18d |\n",
            produtos[indiceMaior].codigoItem,
            produtos[indiceMaior].nomeItem,
            produtos[indiceMaior].quantidadeTotal);
    } else {
        printf("Nenhuma venda encontrada para o dia %s.\n", dataConsulta);
    }
    color_printf("----------------------------------------------------\n", COLOR_WHITE);
}

void exibirProdutoMenosVendidoPorDia(Venda vendas[], int *numVendas, const char *dataConsulta) {
    ProdutoVendido produtos[100];
    int numProdutos = 0;

    if (*numVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        color_printf("----------------------------------------------------------\n", COLOR_WHITE);
        return;
    }

    // Somar quantidades por código de item
    for (int i = 0; i < *numVendas; i++) {
        if (strcmp(vendas[i].data.dateStr, dataConsulta) != 0) continue;

        int encontrado = 0;
        
        // Procurar se o código já existe no array
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].codigoItem == vendas[i].codigoItem) {
                produtos[j].quantidadeTotal += vendas[i].quantidade;
                encontrado = 1;
                break;
            }
        }
        // Se não encontrado, adicionar novo produto
        if (!encontrado) {
            produtos[numProdutos].codigoItem = vendas[i].codigoItem;
            strcpy(produtos[numProdutos].nomeItem, vendas[i].nomeItem);
            produtos[numProdutos].quantidadeTotal = vendas[i].quantidade;
            numProdutos++;
        }
    }

    // Encontrar o produto com menor quantidade
    int menorQuantidade = INT_MAX; // Garantir que qualquer quantidade será menor
    int indiceMenor = -1;
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].quantidadeTotal < menorQuantidade) {
            menorQuantidade = produtos[i].quantidadeTotal;
            indiceMenor = i;
        }
    }

    // Exibir resultado
    if (indiceMenor != -1) {
        printf("\n------ Produto menos vendido do dia %s -----\n", dataConsulta);
        printf("| %4s | %-20s | %s |\n", "Item", "Nome", "Quantidade Vendida");
        printf("| %4d | %-20s | %18d |\n",
            produtos[indiceMenor].codigoItem,
            produtos[indiceMenor].nomeItem,
            produtos[indiceMenor].quantidadeTotal);
    } else {
        printf("Nenhuma venda encontrada para o dia %s.\n", dataConsulta);
    }
    color_printf("----------------------------------------------------\n", COLOR_WHITE);
}

// Opção 1: Registrar uma venda
// - registrar uma venda
// - resumoCompra()
// }

// Opção 2: Listar todas as vendas do dia em ordem decrescente de faturamento
// - listar o resumo de vendas do dia em ordem decrescente de faturamento
// - Soma da quantidade dos itens vendidos

// Opção 3: Exibir o faturamento total do dia

// Opção 4: Exibir a quantidade de clientes atendidos no dia

// Opção 5: Exibir o produto mais vendido do dia

// Opção 6: Exibir o produto menos vendido do dia

// Opção 7: Sair