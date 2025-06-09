#include <stdio.h>
#include <string.h>
#include "include/venda.h"
#include "include/utils.h"
#include "include/relatorios.h"

int main() {
    Venda vendas[MAX_VENDAS];
    Venda novaVenda;
    int numVendas;
    int proximoIdCliente;


    numVendas = carregarVendas(vendas);
    if (numVendas > 0) {
        printf("%d registros de vendas carregados do arquivo.\n", numVendas);
        // Determina o próximo ID de cliente baseado nos dados carregados
        // Encontra o maior idCliente existente e adiciona 1
        int maxId = 0;
        int i;
        for(i = 0; i < numVendas; i++) {
            if (vendas[i].idCliente > maxId) {
                maxId = vendas[i].idCliente;
            }
        }
        proximoIdCliente = maxId + 1;
    } else {
        printf("Nenhum registro de venda encontrado. Iniciando com ID de cliente 1.\n");
        proximoIdCliente = 1; // Garante que começa em 1 se não houver vendas
    }

    int isRunning = 1;

    while (isRunning) {
        menu();

        int option;
        scanf("%d", &option);

        limparTerminal();

        switch (option) {
            case 1:
                if (numVendas >= MAX_VENDAS) {
                    color_printf("Limite máximo de vendas atingido.\n", COLOR_RED);
                    break;
                }

                Venda novaVenda;

                // Atribui o ID do cliente atual à nova venda.
                // Este ID representa a "entidade" que está comprando agora.
                novaVenda.idCliente = proximoIdCliente;

                printf("--- Registrar Nova Venda ---\n");
                printf("Digite o código do item: ");
                scanf("%d", &novaVenda.codigoItem);
                limparBufferEntrada(); 

                printf("Digite o nome do item: ");
                fgets(novaVenda.nomeItem, sizeof(novaVenda.nomeItem), stdin);
                novaVenda.nomeItem[strcspn(novaVenda.nomeItem, "\n")] = 0; // Remove a nova linha

                printf("Digite a marca do item: ");
                fgets(novaVenda.marcaItem, sizeof(novaVenda.marcaItem), stdin);
                novaVenda.marcaItem[strcspn(novaVenda.marcaItem, "\n")] = 0;

                printf("Digite a quantidade: ");
                scanf("%d", &novaVenda.quantidade);
                limparBufferEntrada();

                printf("Digite o preço unitário: ");
                scanf("%f", &novaVenda.precoUnitario);
                limparBufferEntrada();

                // printf("Digite a data da venda (dd/mm/yyyy): ");
                // scanf("%d/%d/%d", &novaVenda.data.dia, &novaVenda.data.mes, &novaVenda.data.ano);
                // limparBufferEntrada();

                adicionarVenda(vendas, &novaVenda, &numVendas, &proximoIdCliente);
                salvarVendas(vendas, &numVendas);

                break;
            case 2:
                isRunning = 0;
                break;
            default:
                color_printf("Opcao nao implementada ainda.\n", COLOR_YELLOW);
                break;
        }
        limparTerminal();
    }
    return 0;
}