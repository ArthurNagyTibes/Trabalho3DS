// Arquivo principal - main.c
// Este é o ponto de entrada do programa da padaria

#include <stdio.h> // Biblioteca para entrada e saída
#include "padaria.h" // Inclui nosso header

// Função que exibe o menu principal
void exibirMenu() {
    printf("\n======== SISTEMA DA PADARIA ========\n"); // Título
    printf("1 - Cadastrar Itens\n"); // Opção 1
    printf("2 - Ver Estoque\n"); // Opção 2
    printf("3 - Realizar Venda\n"); // Opção 3
    printf("4 - Fechar Caixa\n"); // Opção 4
    printf("====================================\n"); // Linha
    printf("Escolha uma opcao: "); // Pergunta
}

// Função principal
int main() {
    SistemaPadaria padaria; // Declara o sistema da padaria
    int opcao; // Variável para opção escolhida
    char entrada[100]; // Buffer para ler entrada

    inicializarPadaria(&padaria); // Inicializa com zero itens

    printf("====================================\n"); // Linha superior
    printf("        BEM-VINDO A PADARIA!        \n"); // Boas-vindas
    printf("   Paes, Bolos e Muito Mais! :)    \n"); // Slogan
    printf("====================================\n"); // Linha inferior

    opcao = 0; // Começa com zero

    while (opcao != 4) { // Loop até escolher fechar caixa
        exibirMenu(); // Mostra menu

        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &opcao); // Converte texto para número

        switch (opcao) { // Switch para verificar opção
            case 1: // Caso cadastrar itens
                cadastrarVariosItens(&padaria); // Cadastra itens
                pausar(); // Pausa
                break; // Sai do switch

            case 2: // Caso ver estoque
                exibirEstoque(&padaria); // Mostra estoque
                pausar(); // Pausa
                break; // Sai do switch

            case 3: // Caso realizar venda
                realizarVenda(&padaria); // Realiza venda
                pausar(); // Pausa
                break; // Sai do switch

            case 4: // Caso fechar caixa
                printf("\n[CAIXA] Fechando o caixa...\n"); // Mensagem
                printf("Ate logo! Volte sempre! :)\n"); // Despedida
                break; // Sai do switch

            default: // Caso opção inválida
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 4.\n"); // Erro
                pausar(); // Pausa
                break; // Sai do switch
        }
    }

    return 0; // Retorna zero (sucesso)
}
