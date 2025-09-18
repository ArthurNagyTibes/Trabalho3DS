
#include <stdio.h>
#include <locale.h>
#include "comercio-template.h"

int main() {
    setlocale(LC_ALL, "Portuguese"); // Corrigido: aspas fechadas corretamente

    int opcao;
    printf("========================================\n");
    printf("    SISTEMA DE GERENCIAMENTO COMERCIAL\n");
    printf("========================================\n");

    do {
        printf("\n============ MENU PRINCIPAL ============\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Mostrar Estoque\n");
        printf("3. Vender Produto\n");
        printf("4. Buscar Produto\n");
        printf("0. Sair\n");
        printf("========================================\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                mostrarEstoque();
                break;
            case 3:
                venderProduto();
                break;
            case 4: {
                int codigo;
                printf("Digite o código do produto: ");
                scanf("%d", &codigo);
                int indice = buscarProduto(codigo);
                if (indice != -1) {
                    printf("\n--- PRODUTO ENCONTRADO ---\n");
                    printf("Código: %d\n", estoque[indice].codigo);
                    printf("Nome: %s\n", estoque[indice].nome);
                    printf("Categoria: %s\n", estoque[indice].categoria);
                    printf("Preço: R$ %.2f\n", estoque[indice].preco);
                    printf("Quantidade: %d\n", estoque[indice].quantidade);
                } else {
                    printf("Produto não encontrado!\n");
                }
                break;
            }
            case 0:
                printf("\nObrigado por usar nosso sistema!\n");
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
