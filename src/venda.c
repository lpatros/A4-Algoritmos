#include "../include/venda.h" // Para as definições de Venda e constantes
#include "../include/utils.h" // Para limparBufferEntrada
#include <stdio.h>
#include <string.h>
#include <ctype.h>   // Para toupper
#include <stdlib.h>  // Se fosse necessário para outras funções aqui

// Função auxiliar, pode ser estática pois só é usada aqui
static float calcularPrecoTotal(int quantidade, float precoUnitario) {
    float total = quantidade * precoUnitario;
    if (quantidade >= 3) {
        total *= 0.90; // Aplica desconto de 10%
    }
    return total;
}

void adicionarVenda(Venda vendas[], int *numVendas, int *proximoIdCliente) {
    char continuar;
    char dataVenda[11];

    printf("\n--- Registro de Nova Venda ---\n");
    printf("Digite a data da venda (dd/mm/yyyy): ");
    scanf("%10s", dataVenda);
    limparBufferEntrada();

    do {
        if (*numVendas >= MAX_VENDAS) {
            printf("Erro: Limite maximo de vendas atingido.\n");
            return;
        }

        Venda *v = &vendas[*numVendas]; // Ponteiro para a próxima posição livre

        strcpy(v->data, dataVenda);
        v->idCliente = *proximoIdCliente;

        printf("\nDigite o codigo do item: ");
        scanf("%d", &v->codigoItem);
        limparBufferEntrada();

        printf("Digite o nome do item: ");
        fgets(v->nomeItem, 50, stdin);
        v->nomeItem[strcspn(v->nomeItem, "\n")] = 0; // Remove a nova linha

        printf("Digite a marca do item: ");
        fgets(v->marcaItem, 50, stdin);
        v->marcaItem[strcspn(v->marcaItem, "\n")] = 0;

        printf("Digite a quantidade de itens: ");
        scanf("%d", &v->quantidade);

        printf("Digite o preco unitario do item: ");
        scanf("%f", &v->precoUnitario);
        limparBufferEntrada();

        v->precoTotal = calcularPrecoTotal(v->quantidade, v->precoUnitario);
        printf("-> Preco total do item (com desconto, se aplicavel): R$ %.2f\n", v->precoTotal);

        (*numVendas)++;

        printf("\nDeseja adicionar outro item para este mesmo cliente? (S/N): ");
        scanf(" %c", &continuar);
        limparBufferEntrada();

    } while (toupper(continuar) == 'S');

    (*proximoIdCliente)++; // Incrementa o ID para o próximo cliente
    printf("\nVenda registrada com sucesso!\n");
}

void salvarVendas(Venda vendas[], int numVendas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    int i;
    for (i = 0; i < numVendas; i++) {
        fprintf(arquivo, "%s;%d;%d;%s;%s;%d;%.2f;%.2f\n",
                vendas[i].data, vendas[i].idCliente, vendas[i].codigoItem,
                vendas[i].nomeItem, vendas[i].marcaItem, vendas[i].quantidade,
                vendas[i].precoUnitario, vendas[i].precoTotal);
    }

    fclose(arquivo);
}

int carregarVendas(Venda vendas[]) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        // Não é um erro fatal, apenas informa que um novo arquivo será criado
        // printf("Arquivo de dados nao encontrado. Um novo sera criado ao salvar.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_VENDAS &&
           fscanf(arquivo, "%10[^;];%d;%d;%49[^;];%49[^;];%d;%f;%f\n",
                  vendas[count].data, &vendas[count].idCliente, &vendas[count].codigoItem,
                  vendas[count].nomeItem, vendas[count].marcaItem, &vendas[count].quantidade,
                  &vendas[count].precoUnitario, &vendas[count].precoTotal) == 8) {
        count++;
    }

    fclose(arquivo);
    // printf("%d registros de vendas carregados do arquivo.\n", count); // Movido para main para melhor feedback inicial
    return count;
}