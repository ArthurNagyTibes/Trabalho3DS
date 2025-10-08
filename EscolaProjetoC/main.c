// Arquivo principal - main.c
// Este � o ponto de entrada do programa da padaria

#include <stdio.h> // Biblioteca para entrada e sa�da
#include "padaria.h" // Inclui nosso header

// Fun��o que exibe o menu principal
void exibirMenu() {
    printf("\n======== SISTEMA DA PADARIA ========\n"); // T�tulo
    printf("1 - Cadastrar Itens\n"); // Op��o 1
    printf("2 - Ver Estoque\n"); // Op��o 2
    printf("3 - Realizar Venda\n"); // Op��o 3
    printf("4 - Fechar Caixa\n"); // Op��o 4
    printf("====================================\n"); // Linha
    printf("Escolha uma opcao: "); // Pergunta
}

// Fun��o principal
int main() {
    SistemaPadaria padaria; // Declara o sistema da padaria
    int opcao; // Vari�vel para op��o escolhida
    char entrada[100]; // Buffer para ler entrada

    inicializarPadaria(&padaria); // Inicializa com zero itens

    printf("====================================\n"); // Linha superior
    printf("        BEM-VINDO A PADARIA!        \n"); // Boas-vindas
    printf("   Paes, Bolos e Muito Mais! :)    \n"); // Slogan
    printf("====================================\n"); // Linha inferior

    opcao = 0; // Come�a com zero

    while (opcao != 4) { // Loop at� escolher fechar caixa
        exibirMenu(); // Mostra menu

        fgets(entrada, 100, stdin); // L� entrada como texto
        sscanf(entrada, "%d", &opcao); // Converte texto para n�mero

        switch (opcao) { // Switch para verificar op��o
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

            default: // Caso op��o inv�lida
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 4.\n"); // Erro
                pausar(); // Pausa
                break; // Sai do switch
        }
    }

    return 0; // Retorna zero (sucesso)
}
