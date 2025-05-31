#ifndef VENDA_H
#define VENDA_H

#define MAX_VENDAS 1000
#define NOME_ARQUIVO "loja_roupa.txt"

typedef struct {
    char data[11];
    int idCliente;
    int codigoItem;
    char nomeItem[50];
    char marcaItem[50];
    int quantidade;
    float precoUnitario;
    float precoTotal;     // (quantidade * precoUnitario) com desconto
} Venda;

// Protótipos das Funções de Operação de Vendas
void adicionarVenda(Venda vendas[], int *numVendas, int *proximoIdCliente);
void salvarVendas(Venda vendas[], int numVendas);
int carregarVendas(Venda vendas[]);
// calcularPrecoTotal pode ser static em vendas_operacoes.c se só for usada lá

#endif