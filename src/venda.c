#include "../include/venda.h"
#include "../include/utils.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

static float calcularPrecoTotal(int, float);

void adicionarVenda(Venda vendas[], Venda *novaVenda, int *numVendas, int *proximoIdCliente) {
    novaVenda->precoTotal = calcularPrecoTotal(novaVenda->quantidade, novaVenda->precoUnitario);
    
    // Obter a data atual
    time_t t = time(NULL);
    struct tm *data_atual_info = localtime(&t);
    
    // Verificar se localtime retornou um ponteiro válido
    if (data_atual_info != NULL) {
        novaVenda->data.dia = data_atual_info->tm_mday;
        novaVenda->data.mes = data_atual_info->tm_mon + 1;     // tm_mon é 0-11 (janeiro = 0)
        novaVenda->data.ano = data_atual_info->tm_year + 1900; // tm_year é o número de anos desde 1900
    } else {
        novaVenda->data.dia = 0;
        novaVenda->data.mes = 0;
        novaVenda->data.ano = 0;
        color_printf("Erro ao obter a data atual. Usando data padrao (0/0/0).\n", COLOR_RED);
    }
    // Formata a data para o formato "DD/MM/AAAA"
    sprintf(novaVenda->data.dateStr, "%02d/%02d/%04d", novaVenda->data.dia, novaVenda->data.mes, novaVenda->data.ano);
    
    // Adiciona a nova venda ao array de vendas
    vendas[*numVendas] = *novaVenda;
    (*numVendas)++;
    
    // Após a venda ser concluída para este cliente,
    // incrementa o ID para o próximo.
    (*proximoIdCliente)++;
    
    color_printf("Venda registrada com sucesso!\n", COLOR_GREEN);
}

void salvarVendas(Venda vendas[], int *numVendas) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    int i;
    for (i = 0; i < *numVendas; i++) {
        fprintf(arquivo, "%s %d %d %s %s %d %.2f %.2f\n",
                vendas[i].data.dateStr,
                vendas[i].idCliente, vendas[i].codigoItem,
                vendas[i].nomeItem, vendas[i].marcaItem, vendas[i].quantidade,
                vendas[i].precoUnitario, vendas[i].precoTotal);
    }
    fclose(arquivo);
}

int carregarVendas(Venda vendas[]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        return 0;
    }

    int count = 0;
    while (count < MAX_VENDAS &&
        fscanf(
            arquivo,
            "%10s %d %d %49[^ ] %49[^ ] %d %f %f\n",
            vendas[count].data.dateStr,
            &vendas[count].idCliente,
            &vendas[count].codigoItem,
            vendas[count].nomeItem,
            vendas[count].marcaItem,
            &vendas[count].quantidade,
            &vendas[count].precoUnitario,
            &vendas[count].precoTotal) == 8) {
        
        sscanf(
            vendas[count].data.dateStr, "%d/%d/%d",
            &vendas[count].data.dia,
            &vendas[count].data.mes,
            &vendas[count].data.ano
        );
        count++;
    }

    fclose(arquivo);
    return count;
}

static float calcularPrecoTotal(int quantidade, float precoUnitario) {
    float total = quantidade * precoUnitario;
    if (quantidade >= 3) {
        total *= 0.90; // Aplica desconto de 10%
    }
    return total;
}