// Arquivo de cabe�alho - padaria.h
// Este arquivo declara as fun��es e estruturas que vamos usar no programa

#ifndef PADARIA_H // Previne inclus�o dupla do header
#define PADARIA_H // Define o identificador do header

#define MAX_ITENS 100 // N�mero m�ximo de itens da padaria
#define MAX_NOME 50 // Tamanho m�ximo do nome do item

// Estrutura que representa um item da padaria
typedef struct {
    int codigo; // C�digo �nico do item
    char nome[MAX_NOME]; // Nome do item (p�o, bolo, etc)
    float preco; // Pre�o unit�rio do item
    int estoque; // Quantidade dispon�vel em estoque
} ItemPadaria;

// Estrutura que guarda todos os itens da padaria
typedef struct {
    ItemPadaria itens[MAX_ITENS]; // Array com todos os itens
    int totalItens; // Quantidade de itens cadastrados
} SistemaPadaria;

// Declara��o das fun��es
void inicializarPadaria(SistemaPadaria *padaria); // Inicializa a padaria
void cadastrarVariosItens(SistemaPadaria *padaria); // Cadastra v�rios itens
void exibirEstoque(SistemaPadaria *padaria); // Mostra todos os itens
void realizarVenda(SistemaPadaria *padaria); // Realiza uma venda
void limparBuffer(); // Limpa o buffer do teclado
void pausar(); // Pausa o programa

#endif // Fim do header
