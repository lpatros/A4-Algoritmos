#include "../include/relatorios.h"
#include "../include/utils.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para qsort

// Função de comparação para qsort, estática pois só é usada aqui
static int compararVendas(const void *a, const void *b) {
    Venda *vendaA = (Venda *)a;
    Venda *vendaB = (Venda *)b;
    if (vendaB->precoTotal > vendaA->precoTotal) return 1;
    if (vendaB->precoTotal < vendaA->precoTotal) return -1;
    return 0;
}

void gerarRelatorios(Venda vendas[], int numVendas) {
    if (numVendas == 0) {
        printf("\nNao ha dados de vendas para gerar relatorios.\n");
        return;
    }

    char dataRelatorio[11];
    printf("\n--- Geracao de Relatorios ---\n");
    printf("Digite a data para a qual deseja gerar os relatorios (dd/mm/yyyy): ");
    scanf("%10s", dataRelatorio);
    limparBufferEntrada();

    // 1. Quantidade total de itens vendidos no dia
    int totalItensDia = 0;
    int i;
    for (i= 0; i < numVendas; i++) {
        if (strcmp(vendas[i].data, dataRelatorio) == 0) {
            totalItensDia += vendas[i].quantidade;
        }
    }
    printf("\n-------------------------------------------------------------");
    printf("\n1. Quantidade Total de Itens Vendidos em %s: %d\n", dataRelatorio, totalItensDia);

    // Cria um array temporário com as vendas da data especificada
    Venda vendasDoDia[MAX_VENDAS]; // Reutiliza MAX_VENDAS, poderia ser numVendas se garantido < MAX_VENDAS
    int numVendasDia = 0;
    int j;
    for (j = 0; j < numVendas; j++) {
        if (strcmp(vendas[j].data, dataRelatorio) == 0) {
            if (numVendasDia < MAX_VENDAS) { // Segurança adicional
                 vendasDoDia[numVendasDia++] = vendas[j];
            }
        }
    }

    // 2. Listar todas as vendas em ordem decrescente de valor
    qsort(vendasDoDia, numVendasDia, sizeof(Venda), compararVendas);
    printf("\n2. Lista de Vendas em %s (Ordem Decrescente de Valor):\n", dataRelatorio);
    if (numVendasDia == 0) {
        printf("   Nenhuma venda encontrada para esta data.\n");
    } else {
        printf("   %-15s | %-20s | %-10s | %-10s\n", "Cliente (ID)", "Item", "Qtd", "Valor Total");
        printf("   ----------------------------------------------------------\n");
        int a;
        for (a = 0; a < numVendasDia; a++) {
            printf("   %-15d | %-20s | %-10d | R$ %-8.2f\n",
                   vendasDoDia[a].idCliente, vendasDoDia[a].nomeItem,
                   vendasDoDia[a].quantidade, vendasDoDia[a].precoTotal);
        }
    }

    // 3. Faturamento bruto diário
    float faturamentoBruto = 0;
    int x;
    for (x = 0; x < numVendasDia; x++) {
        faturamentoBruto += vendasDoDia[x].precoTotal;
    }
    printf("\n3. Faturamento Bruto em %s: R$ %.2f\n", dataRelatorio, faturamentoBruto);

    // 4. Quantidade de clientes que compraram no dia
    int clientesUnicosDia[MAX_VENDAS]; // Para armazenar IDs de clientes únicos
    int numClientesUnicosDia = 0;
    int b;
    for (b = 0; b < numVendasDia; b++) {
        int encontrado = 0;
        int c;
        for (c = 0; c < numClientesUnicosDia; c++) {
            if (vendasDoDia[b].idCliente == clientesUnicosDia[c]) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            if (numClientesUnicosDia < MAX_VENDAS) { // Segurança adicional
                clientesUnicosDia[numClientesUnicosDia++] = vendasDoDia[b].idCliente;
            }
        }
    }
    printf("\n4. Quantidade de Clientes (unicos) em %s: %d\n", dataRelatorio, numClientesUnicosDia);


    // 5 & 6. Item mais e menos vendido
    if (numVendasDia > 0) {
        // Estrutura para agregar quantidades por item (local à função)
        typedef struct {
            int codigo;
            char nome[50];
            int qtdTotal;
        } ItemAgregado;

        ItemAgregado itensAgregados[MAX_VENDAS]; // Potencialmente muitos itens diferentes
        int numItensAgregados = 0;

        int h;
        for (h = 0; h < numVendasDia; h++) {
            int encontrado = 0;
            int k;
            for (k = 0; k < numItensAgregados; k++) {
                if (vendasDoDia[h].codigoItem == itensAgregados[k].codigo) {
                    itensAgregados[k].qtdTotal += vendasDoDia[h].quantidade;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                if (numItensAgregados < MAX_VENDAS) { // Segurança
                    itensAgregados[numItensAgregados].codigo = vendasDoDia[h].codigoItem;
                    strcpy(itensAgregados[numItensAgregados].nome, vendasDoDia[h].nomeItem);
                    itensAgregados[numItensAgregados].qtdTotal = vendasDoDia[h].quantidade;
                    numItensAgregados++;
                }
            }
        }

        if (numItensAgregados > 0) {
            ItemAgregado maisVendido = itensAgregados[0];
            ItemAgregado menosVendido = itensAgregados[0];

            int indice;
            for (indice = 1; indice < numItensAgregados; indice++) {
                if (itensAgregados[indice].qtdTotal > maisVendido.qtdTotal) {
                    maisVendido = itensAgregados[indice];
                }
                if (itensAgregados[indice].qtdTotal < menosVendido.qtdTotal) {
                    menosVendido = itensAgregados[indice];
                }
            }
            printf("\n5. Item Mais Vendido em %s: %s (Cod: %d, Total: %d unidades)\n", dataRelatorio, maisVendido.nome, maisVendido.codigo, maisVendido.qtdTotal);
            printf("\n6. Item Menos Vendido em %s: %s (Cod: %d, Total: %d unidades)\n", dataRelatorio, menosVendido.nome, menosVendido.codigo, menosVendido.qtdTotal);
        } else {
             printf("\n5. Item Mais Vendido: N/A (nenhum item agregado)\n");
             printf("\n6. Item Menos Vendido: N/A (nenhum item agregado)\n");
        }

    } else {
        printf("\n5. Item Mais Vendido: N/A (sem vendas na data)\n");
        printf("\n6. Item Menos Vendido: N/A (sem vendas na data)\n");
    }
    printf("-------------------------------------------------------------\n");
}