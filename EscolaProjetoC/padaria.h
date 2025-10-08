// Arquivo de cabeçalho - padaria.h
// Este arquivo declara as funções e estruturas que vamos usar no programa

#ifndef PADARIA_H // Previne inclusão dupla do header
#define PADARIA_H // Define o identificador do header

#define MAX_ITENS 100 // Número máximo de itens da padaria
#define MAX_NOME 50 // Tamanho máximo do nome do item

// Estrutura que representa um item da padaria
typedef struct {
    int codigo; // Código único do item
    char nome[MAX_NOME]; // Nome do item (pão, bolo, etc)
    float preco; // Preço unitário do item
    int estoque; // Quantidade disponível em estoque
} ItemPadaria;

// Estrutura que guarda todos os itens da padaria
typedef struct {
    ItemPadaria itens[MAX_ITENS]; // Array com todos os itens
    int totalItens; // Quantidade de itens cadastrados
} SistemaPadaria;

// Declaração das funções
void inicializarPadaria(SistemaPadaria *padaria); // Inicializa a padaria
void cadastrarVariosItens(SistemaPadaria *padaria); // Cadastra vários itens
void exibirEstoque(SistemaPadaria *padaria); // Mostra todos os itens
void realizarVenda(SistemaPadaria *padaria); // Realiza uma venda
void limparBuffer(); // Limpa o buffer do teclado
void pausar(); // Pausa o programa

#endif // Fim do header
