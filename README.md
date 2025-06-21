# A4 - Algoritmos e Laboratorio de Programacao

## Sumário
- [Enunciado](#enunciado)
  - [Situação-Problema](#situação-problema)
  - [Metodologia](#metodologia)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Compilar e Rodar o Projeto](#como-compilar-e-rodar-o-projeto)
  - [Pré-requisitos](#pré-requisitos)
  - [Compilação](#compilação)
  - [Execução](#execução)

## Enunciado

### Situação-Problema

A atividade de implementação e desenvolvimento de um sistema envolve diversas estruturas de programação, independentemente da linguagem de programação escolhida. Neste viés, você deverá desenvolver um PROGRAMA EM LIGUAGEM C, que permita **registrar as vendas diárias de uma loja de roupas**, imprimindo no final do dia, os seguintes **relatórios**:

- Quantidade total de itens vendidos no dia, no ato do registro da venda, ou seja, assim que finalizar aquela venda específica;
- Listar todas as vendas realizadas no dia, em ordem decrescente, ou seja, considerar a venda de maior valor prioritariamente, e assim por diante, até que todas sejam listadas. O usuário informará a data da venda;
- Faturamento bruto diário sob as vendas (o usuário digitará a data);
- Quantidade de clientes que realizaram compras naquele dia (o usuário digitará a data);
- Item mais vendido em uma determinada data informada pelo usuário;
- Item menos vendido em uma determinada data informada pelo usuário.

### Metodologia

Escreva um programa em Linguagem C que obedeça as seguintes diretivas:

- Cadastrar os seguintes dados por venda realizada: **código** do item, **nome** do item, **marca** do item, **quantidade** de itens e **preço unitário** do item;
- Após cada entrada de novo item, o programa deverá **chamar uma função para calcular automaticamente o preço pago na venda** realizada para cada item registrado;
- O programa deverá atribuir um **desconto de 10%** do valor total da venda realizada para cada item, sempre que a quantidade de itens vendidos for **maior ou igual a três unidades**;
- O programa também deverá calcular automaticamente a **quantidade de clientes que realizaram compras naquele dia**.

No final do dia, ou seja, quando não tiverem novos clientes a serem registrados, o programa deverá ser finalizado, gerando os seguintes **Relatórios Gerenciais**:

- Quantidade total de itens vendidos no dia, no ato do registro da venda, ou seja, assim que finalizar aquela venda específica;
- Listar todas as vendas realizadas no dia, **em ordem decrescente**, ou seja, considerar a venda de maior valor prioritariamente, e assim por diante, até que todas sejam listadas. O usuário informará a data da venda;
- Faturamento bruto diário sob as vendas (o usuário digitará a data);
- Quantidade de clientes que realizaram compras naquele dia (o usuário digitará a data);
- Item mais vendido em uma determinada data informada pelo usuário;
- Item menos vendido em uma determinada data informada pelo usuário.

Você deverá obedecer, obrigatoriamente, os seguintes critérios:

- Utilizar **struct**, **array**, **algoritmo de ordenação**, **funções**, **modularização**.
- Gravar os dados no FILE `loja_roupa.dat` ou `loja_roupa.txt`.
- Implementar a solução algorítmica em **linguagem C**.
- Apresentar os testes realizados, ou seja, inserir os valores de entrada e mostrar os resultados obtidos (saída).
- Para que seja validado o critério 4, será necessário realizar, ao menos três testes com entrada de dados distintas para cada um deles.

## Funcionalidades Implementadas

O sistema de registro de venda da loja de roupas oferece as seguintes funcionalidades:

1.  **Registro de venda:**
    *   Cadastro de itens por venda: código, nome, marca, quantidade e preço unitário.
    *   Cálculo automático do preço pago por item.
    *   Aplicação de desconto de 10% para compras com 3 ou mais unidades do mesmo item.
2.  **Relatórios Gerenciais:**
    *   Quantidade total de itens vendidos (após cada venda).
    *   Listagem de vendas do dia em ordem decrescente de valor (por data).
    *   Faturamento bruto diário (por data).
    *   Quantidade de clientes que realizaram compras no dia (por data).
    *   Item mais vendido em uma data específica.
    *   Item menos vendido em uma data específica.
3.  **Persistência de Dados:**
    *   Os dados das vendas são armazenados no FILE `loja_roupa.txt`.

## Tecnologias Utilizadas

- Linguagem C

## Estrutura do Projeto

```
.
├── data/
│   └── loja_roupa.txt    # FILE de dados das vendas
├── include/
│   ├── relatorios.h      # Cabeçalho para as funções de relatórios
│   ├── utils.h           # Cabeçalho para as funções utilitárias
│   └── venda.h           # Cabeçalho para as funções de venda
├── src/
│   ├── relatorios.c      # Implementação das funções de geração de relatórios
│   ├── venda.c           # Implementação das funções de registro e manipulação de vendas
├── utils/
│   └── utils.c           # Implementação das funções utilitárias
├── .gitignore            # Especifica FILEs intencionalmente não rastreados pelo Git
├── main.c                # FILE principal com o menu e fluxo do programa
└── README.md             # Documentação do projeto
```

## Como Compilar e Rodar o Projeto

### Pré-requisitos

- Compilador C (GCC recomendado)

### Compilação

Abra o terminal na pasta raiz do projeto e execute o seguinte comando:

```bash
gcc main.c include/*/*.c utils/*.c -o main
```

### Execução

Após a compilação bem-sucedida, um FILE executável chamado `main` (ou `main.exe` no Windows) será gerado. Para rodar o programa, execute:

No Linux/macOS:
```bash
./main
```

No Windows:
```bash
./main.exe
```
