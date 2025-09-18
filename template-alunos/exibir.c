#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "comercio-template.h"

Produto estoque[MAX];  // Vetor global que armazena os produtos
int totalProdutos = 0; // Contador global de produtos

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarProduto(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].codigo == codigo) {
            return i; // Retorna o índice do produto
        }
    }
    return -1; // Produto não encontrado
}

void cadastrarProduto() {
    if (totalProdutos >= MAX) {
        printf("\n ERRO: Estoque lotado! Não é possível cadastrar mais produtos.\n");
        return;
    }

    printf("\n========== CADASTRO DE PRODUTO ==========\n");

    int codigo;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    limparBuffer();

    // Verifica se o código já existe
    if (buscarProduto(codigo) != -1) {
        printf(" ERRO: Já existe um produto com este código!\n");
        return;
    }

    estoque[totalProdutos].codigo = codigo;

    printf("Digite o nome do produto: ");
    fgets(estoque[totalProdutos].nome, sizeof(estoque[totalProdutos].nome), stdin);
    estoque[totalProdutos].nome[strcspn(estoque[totalProdutos].nome, "\n")] = 0; // Remove quebra de linha

    printf("Digite a categoria do produto: ");
    fgets(estoque[totalProdutos].categoria, sizeof(estoque[totalProdutos].categoria), stdin);
    estoque[totalProdutos].categoria[strcspn(estoque[totalProdutos].categoria, "\n")] = 0;

    printf("Digite o preço do produto: R$ ");
    scanf("%f", &estoque[totalProdutos].preco);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &estoque[totalProdutos].quantidade);

    totalProdutos++;

    printf("\n Produto cadastrado com sucesso!\n");
    printf("========================================\n");
}

void venderProduto() {
    if (totalProdutos == 0) {
        printf("\n Não há produtos cadastrados para venda!\n");
        return;
    }

    printf("\n============ VENDA DE PRODUTO ============\n");

    int codigo, quantidade;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);

    int indice = buscarProduto(codigo);
    if (indice == -1) {
        printf(" Produto não encontrado!\n");
        return;
    }

    printf("\n--- PRODUTO SELECIONADO ---\n");
    printf("Nome: %s\n", estoque[indice].nome);
    printf("Preço unitário: R$ %.2f\n", estoque[indice].preco);
    printf("Quantidade disponível: %d\n", estoque[indice].quantidade);

    if (estoque[indice].quantidade == 0) {
        printf(" Produto fora de estoque!\n");
        return;
    }

    printf("\nDigite a quantidade a vender: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf(" Quantidade inválida!\n");
        return;
    }

    if (quantidade > estoque[indice].quantidade) {
        printf(" Quantidade insuficiente em estoque!\n");
        printf("Disponível: %d unidades\n", estoque[indice].quantidade);
        return;
    }

    // Realiza a venda
    float total = quantidade * estoque[indice].preco;
    estoque[indice].quantidade -= quantidade;

    printf("\n========== COMPROVANTE DE VENDA ==========\n");
    printf("Produto: %s\n", estoque[indice].nome);
    printf("Quantidade vendida: %d\n", quantidade);
    printf("Preço unitário: R$ %.2f\n", estoque[indice].preco);
    printf("Total da venda: R$ %.2f\n", total);
    printf("Quantidade restante: %d\n", estoque[indice].quantidade);
    printf("=========================================\n");
    printf(" Venda realizada com sucesso!\n");
}
