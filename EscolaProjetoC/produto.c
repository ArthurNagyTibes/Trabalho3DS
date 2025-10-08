// Arquivo de implementação - padaria.c
// Aqui implementamos todas as funções declaradas no header

#include <stdio.h> // Biblioteca para printf, scanf, etc
#include <string.h> // Biblioteca para manipular strings
#include "padaria.h" // Inclui nosso header

// Função que inicializa a padaria zerada
void inicializarPadaria(SistemaPadaria *padaria) {
    padaria->totalItens = 0; // Começa com zero itens cadastrados
}

// Função que limpa o buffer do teclado
void limparBuffer() {
    int c; // Variável para guardar cada caractere
    while ((c = getchar()) != '\n' && c != EOF); // Lê até encontrar enter
}

// Função que pausa o programa
void pausar() {
    printf("\nPressione ENTER para continuar..."); // Mensagem
    limparBuffer(); // Limpa buffer e espera enter
}

// Função para cadastrar VÁRIOS itens de uma vez
void cadastrarVariosItens(SistemaPadaria *padaria) {
    int quantidadeCadastrar; // Quantos itens cadastrar
    char entrada[100]; // Buffer para ler entrada
    int i; // Contador do loop

    printf("\n========= CADASTRO DE ITENS =========\n"); // Título
    printf("Quantos itens deseja cadastrar? "); // Pergunta
    fgets(entrada, 100, stdin); // Lê a entrada como texto
    sscanf(entrada, "%d", &quantidadeCadastrar); // Converte texto para número

    if (quantidadeCadastrar <= 0) { // Se for zero ou negativo
        printf("[ERRO] Quantidade deve ser maior que zero!\n"); // Erro
        return; // Sai da função
    }

    if (padaria->totalItens + quantidadeCadastrar > MAX_ITENS) { // Se ultrapassar limite
        printf("[ERRO] Limite maximo de itens atingido!\n"); // Erro
        return; // Sai
    }

    // Loop para cadastrar cada item
    i = 0; // Começa do zero
    while (i < quantidadeCadastrar) { // Enquanto não cadastrar todos
        ItemPadaria novoItem; // Cria um item novo
        int codigoExiste; // Variável para verificar se código existe
        int j; // Contador auxiliar

        printf("\n--- Item %d de %d ---\n", i + 1, quantidadeCadastrar); // Mostra progresso

        // Lê o código do item
        printf("Codigo do item: "); // Pergunta código
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &novoItem.codigo); // Converte para número

        // Verifica se o código já existe
        codigoExiste = 0; // Assume que não existe
        j = 0; // Começa do primeiro item
        while (j < padaria->totalItens) { // Percorre itens cadastrados
            if (padaria->itens[j].codigo == novoItem.codigo) { // Se achou igual
                codigoExiste = 1; // Marca que existe
                break; // Para de procurar
            }
            j = j + 1; // Vai pro próximo
        }

        if (codigoExiste == 1) { // Se código já existe
            printf("[ERRO] Codigo ja cadastrado!\n"); // Erro
            printf("[ALERTA] Item nao cadastrado. Continuando...\n"); // Aviso
            i = i + 1; // Vai pro próximo
            continue; // Pula para próxima iteração
        }

        // Lê o nome do item
        printf("Nome do item (ex: Pao Frances, Bolo de Chocolate): "); // Pergunta nome
        fgets(novoItem.nome, MAX_NOME, stdin); // Lê o nome
        novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove enter

        if (strlen(novoItem.nome) == 0) { // Se nome vazio
            printf("[ERRO] Nome nao pode ser vazio!\n"); // Erro
            printf("[ALERTA] Item nao cadastrado. Continuando...\n"); // Aviso
            i = i + 1; // Vai pro próximo
            continue; // Pula
        }

        // Lê o preço
        printf("Preco (use ponto, ex: 5.50): R$ "); // Pergunta preço
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%f", &novoItem.preco); // Converte para float

        if (novoItem.preco <= 0) { // Se preço zero ou negativo
            printf("[ERRO] Preco deve ser maior que zero!\n"); // Erro
            printf("[ALERTA] Item nao cadastrado. Continuando...\n"); // Aviso
            i = i + 1; // Vai pro próximo
            continue; // Pula
        }

        // Lê a quantidade em estoque
        printf("Quantidade em estoque: "); // Pergunta estoque
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &novoItem.estoque); // Converte para número

        if (novoItem.estoque <= 0) { // Se estoque zero ou negativo
            printf("[ERRO] Estoque deve ser maior que zero!\n"); // Erro
            printf("[ALERTA] Item nao cadastrado. Continuando...\n"); // Aviso
            i = i + 1; // Vai pro próximo
            continue; // Pula
        }

        // Item válido - adiciona no sistema
        padaria->itens[padaria->totalItens] = novoItem; // Adiciona no array
        padaria->totalItens = padaria->totalItens + 1; // Incrementa total

        printf("[SUCESSO] Item '%s' cadastrado!\n", novoItem.nome); // Confirma

        i = i + 1; // Vai pro próximo item
    }

    printf("\n[INFO] Cadastro finalizado! Total: %d itens\n", padaria->totalItens); // Mostra total
}

// Função que exibe todo o estoque
void exibirEstoque(SistemaPadaria *padaria) {
    int i; // Contador

    printf("\n======== ESTOQUE DA PADARIA ========\n"); // Título

    if (padaria->totalItens == 0) { // Se não tem itens
        printf("[ALERTA] Nenhum item cadastrado!\n"); // Aviso
        printf("====================================\n"); // Linha
        return; // Sai
    }

    i = 0; // Começa do primeiro
    while (i < padaria->totalItens) { // Percorre todos
        printf("Cod: %d | %s | R$ %.2f | Estoque: %d unid.\n",
               padaria->itens[i].codigo,
               padaria->itens[i].nome,
               padaria->itens[i].preco,
               padaria->itens[i].estoque); // Imprime item
        i = i + 1; // Vai pro próximo
    }
    printf("====================================\n"); // Linha
}

// Função principal de venda
void realizarVenda(SistemaPadaria *padaria) {
    int continuar; // 1 = continuar, 0 = parar
    float valorTotal; // Valor total da compra
    int codigosComprados[MAX_ITENS]; // Códigos dos itens comprados
    int quantidadesCompradas[MAX_ITENS]; // Quantidades de cada item
    int totalItens; // Quantos itens diferentes no carrinho
    int codigo; // Código digitado
    int quantidade; // Quantidade digitada
    char entrada[100]; // Buffer para ler entrada
    int i; // Contador
    int encontrou; // Flag se encontrou item
    int indiceItem; // Índice do item encontrado

    if (padaria->totalItens == 0) { // Se não tem itens
        printf("\n[ERRO] Nenhum item cadastrado!\n"); // Erro
        return; // Sai
    }

    printf("\n========== REALIZAR VENDA ==========\n"); // Título
    exibirEstoque(padaria); // Mostra itens

    continuar = 1; // Começa querendo continuar
    valorTotal = 0.0; // Total zerado
    totalItens = 0; // Carrinho vazio

    while (continuar == 1) { // Enquanto quiser adicionar
        printf("\nCodigo do item (0 para finalizar): "); // Pergunta
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &codigo); // Converte para número

        if (codigo == 0) { // Se digitou 0
            if (totalItens == 0) { // Se carrinho vazio
                printf("[ALERTA] Nenhum item no carrinho!\n"); // Aviso
                return; // Sai
            }
            break; // Sai do loop
        }

        // Busca o item pelo código
        encontrou = 0; // Assume que não encontrou
        indiceItem = 0; // Índice inicial
        i = 0; // Contador
        while (i < padaria->totalItens) { // Percorre itens
            if (padaria->itens[i].codigo == codigo) { // Se achou
                encontrou = 1; // Marca que encontrou
                indiceItem = i; // Guarda o índice
                break; // Para de procurar
            }
            i = i + 1; // Próximo item
        }

        if (encontrou == 0) { // Se não encontrou
            printf("[ERRO] Item nao encontrado!\n"); // Erro
            continue; // Volta pro início
        }

        printf("Quantidade desejada: "); // Pergunta quantidade
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &quantidade); // Converte para número

        if (quantidade <= 0) { // Se quantidade zero ou negativa
            printf("[ERRO] Quantidade deve ser maior que zero!\n"); // Erro
            continue; // Volta
        }

        if (quantidade > padaria->itens[indiceItem].estoque) { // Se não tem estoque
            printf("[ERRO] Estoque insuficiente! Disponivel: %d unid.\n",
                   padaria->itens[indiceItem].estoque); // Erro
            continue; // Volta
        }

        // Adiciona no carrinho
        codigosComprados[totalItens] = codigo; // Guarda código
        quantidadesCompradas[totalItens] = quantidade; // Guarda quantidade
        totalItens = totalItens + 1; // Incrementa itens

        valorTotal = valorTotal + (padaria->itens[indiceItem].preco * quantidade); // Soma no total

        printf("[OK] %dx %s adicionado - Subtotal: R$ %.2f\n",
               quantidade,
               padaria->itens[indiceItem].nome,
               padaria->itens[indiceItem].preco * quantidade); // Confirma
    }

    if (totalItens > 0) { // Se tem itens
        int opcaoPagamento; // Opção de pagamento
        float valorPago; // Valor pago em dinheiro
        float troco; // Troco
        int parcelas; // Número de parcelas
        float valorParcela; // Valor de cada parcela

        printf("\n======== RESUMO DO PEDIDO ========\n"); // Título

        i = 0; // Contador
        while (i < totalItens) { // Percorre itens
            int j; // Contador auxiliar
            j = 0; // Começa do primeiro item
            while (j < padaria->totalItens) { // Procura o item
                if (padaria->itens[j].codigo == codigosComprados[i]) { // Se achou
                    printf("%dx %s - R$ %.2f\n",
                           quantidadesCompradas[i],
                           padaria->itens[j].nome,
                           padaria->itens[j].preco * quantidadesCompradas[i]); // Mostra item
                    break; // Para de procurar
                }
                j = j + 1; // Próximo item
            }
            i = i + 1; // Próximo item do carrinho
        }

        printf("\nVALOR TOTAL: R$ %.2f\n", valorTotal); // Mostra total

        // Processa pagamento
        printf("\n===== FORMAS DE PAGAMENTO =====\n"); // Título
        printf("1 - Dinheiro\n"); // Opção 1
        printf("2 - Cartao de Credito\n"); // Opção 2
        printf("3 - Cartao de Debito\n"); // Opção 3
        printf("Escolha: "); // Pergunta
        fgets(entrada, 100, stdin); // Lê entrada como texto
        sscanf(entrada, "%d", &opcaoPagamento); // Converte para número

        switch (opcaoPagamento) { // Switch para verificar opção
            case 1: // Caso dinheiro
                printf("\nValor pago: R$ "); // Pergunta valor
                fgets(entrada, 100, stdin); // Lê entrada como texto
                sscanf(entrada, "%f", &valorPago); // Converte para float

                if (valorPago <= 0) { // Se valor zero ou negativo
                    printf("[ERRO] Valor deve ser maior que zero!\n"); // Erro
                    return; // Sai
                }

                if (valorPago < valorTotal) { // Se pagou menos
                    printf("[ERRO] Valor insuficiente!\n"); // Erro
                    return; // Sai
                }

                troco = valorPago - valorTotal; // Calcula troco
                printf("\n[SUCESSO] Pagamento recebido!\n"); // Confirma
                printf("Troco: R$ %.2f\n", troco); // Mostra troco
                break; // Sai do switch

            case 2: // Caso crédito
                if (valorTotal > 100.0) { // Se pode parcelar
                    printf("\nParcelas (1 a 6): "); // Pergunta
                    fgets(entrada, 100, stdin); // Lê entrada como texto
                    sscanf(entrada, "%d", &parcelas); // Converte para número

                    if (parcelas < 1 || parcelas > 6) { // Se inválido
                        printf("[ERRO] Numero de parcelas invalido!\n"); // Erro
                        return; // Sai
                    }

                    valorParcela = valorTotal / parcelas; // Calcula parcela
                    printf("\n[SUCESSO] Pagamento aprovado!\n"); // Confirma
                    printf("%dx de R$ %.2f\n", parcelas, valorParcela); // Mostra
                }
                else { // Se não pode parcelar
                    printf("\n[SUCESSO] Pagamento aprovado!\n"); // Confirma
                    printf("Valor: R$ %.2f (a vista)\n", valorTotal); // Mostra
                }
                break; // Sai do switch

            case 3: // Caso débito
                printf("\n[SUCESSO] Pagamento aprovado!\n"); // Confirma
                printf("Valor debitado: R$ %.2f\n", valorTotal); // Mostra
                break; // Sai do switch

            default: // Caso opção inválida
                printf("[ERRO] Forma de pagamento invalida!\n"); // Erro
                return; // Sai
        }

        // Atualiza estoque
        i = 0; // Contador
        while (i < totalItens) { // Percorre itens comprados
            int j; // Contador auxiliar
            j = 0; // Começa do primeiro
            while (j < padaria->totalItens) { // Procura item
                if (padaria->itens[j].codigo == codigosComprados[i]) { // Se achou
                    padaria->itens[j].estoque = padaria->itens[j].estoque - quantidadesCompradas[i]; // Subtrai do estoque
                    break; // Para de procurar
                }
                j = j + 1; // Próximo item
            }
            i = i + 1; // Próximo item do carrinho
        }

        printf("\n[SUCESSO] Estoque atualizado!\n"); // Confirma
        printf("\nObrigado pela preferencia! Volte sempre! :)\n"); // Mensagem
        exibirEstoque(padaria); // Mostra estoque atualizado
    }
}
