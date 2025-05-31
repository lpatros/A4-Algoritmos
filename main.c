#include <stdio.h>
#include "include/venda.h"
#include "include/utils.h"
#include "include/relatorios.h"

int main() {
    Venda vendas[MAX_VENDAS];
    int numVendas = 0;
    int proximoIdCliente = 1;
    int opcao;

    // Carrega os dados do arquivo ao iniciar
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


    printf("============================================\n");
    printf("   Sistema de Vendas - Loja de Roupas\n");
    printf("============================================\n");

    do {
        printf("\nMenu Principal:\n");
        printf("1. Registrar Nova Venda (Cliente)\n");
        printf("2. Gerar Relatorios Gerenciais\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { // Verifica se a leitura foi bem sucedida
            printf("Entrada invalida. Por favor, insira um numero.\n");
            limparBufferEntrada();
            opcao = 0; // Reseta a opção para evitar loop infinito se não for número
            continue;  // Volta para o início do loop
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                adicionarVenda(vendas, &numVendas, &proximoIdCliente);
                break;
            case 2:
                gerarRelatorios(vendas, numVendas);
                break;
            case 3:
                printf("Salvando dados e finalizando o programa...\n");
                salvarVendas(vendas, numVendas);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}