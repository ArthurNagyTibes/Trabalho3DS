#ifndef COMERCIO_TEMPLATE_H_INCLUDED
#define COMERCIO_TEMPLATE_H_INCLUDED

#define MAX 100 // Define o máximo de produtos que podem ser cadastrados

typedef struct {
    int codigo;
    char nome[50];
    char categoria[30];
    float preco;
    int quantidade;
} Produto;

extern Produto estoque[MAX];
extern int totalProdutos; // Contador de produtos cadastrados

void mostrarEstoque();
void cadastrarProduto();
void venderProduto();
int buscarProduto(int codigo);
void limparBuffer();

#endif // COMERCIO_TEMPLATE_H_INCLUDED
