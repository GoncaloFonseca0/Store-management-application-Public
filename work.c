#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct dadoscliente
{
    char nome[100];
    char morada[200];
    int telefone;
    int nif;
};

struct dadosprodutos
{
    char nome[50];
    float preco;
    int stock;
    int num;
};

typedef struct
{
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

void obterDataAtual(char *dataAtual)
{
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(dataAtual, 20, "%Y-%m-%d %H:%M:%S", tm_info);
}

void salvar_contador(int contador) // Feito 100 não mexer mais
{
    FILE *contador_arquivo = fopen("contador.txt", "w");

    if (contador_arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo do contador para escrita.\n");
        return;
    }

    fprintf(contador_arquivo, "%d", contador);

    fclose(contador_arquivo);
}

int carregar_contador() // Feito 100 não mexer mais
{
    FILE *contador_arquivo = fopen("contador.txt", "r");

    if (contador_arquivo == NULL)
    {

        return 0;
    }

    int contador;
    fscanf(contador_arquivo, "%d", &contador);

    fclose(contador_arquivo);

    return contador;
}

void inserir_cliente() // Feito 100 não mexer mais
{
    FILE *dados;
    struct dadoscliente cliente;
    int escolha;
    dados = fopen("InfoClientes.txt", "a");

    if (dados == 0)
    {
        printf("*ERRO*\n");
        printf("Arquivo não encontrado");
    }
    else
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Inserir dados do Cliente *\n");
        printf("---------------------------------------------------------------------------------------------\n");
        fflush(stdin);
        printf("Digite o nome do Cliente:");
        fgets(cliente.nome, sizeof(cliente.nome), stdin);
        fflush(stdin);
        printf("Digite a morada do Cliente:");
        fgets(cliente.morada, sizeof(cliente.morada), stdin);
        fflush(stdin);
        printf("Digite o telefone do Cliente:");
        scanf("%d", &cliente.telefone);
        printf("Digite o NIF do Cliente:");
        scanf("%d", &cliente.nif);

        fprintf(dados, "\nCliente:\n");
        fprintf(dados, "Nome: %s", cliente.nome);
        fprintf(dados, "Morada: %s", cliente.morada);
        fprintf(dados, "Telefone: %d\n", cliente.telefone);
        fprintf(dados, "Nif: %d\n", cliente.nif);

        fclose(dados);
    }
    fflush(stdin);
    do
    {
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("Pretende inserir mais algum cliente?\n");
        printf("1- Sim\n");
        printf("2- Não\n");
        printf("R:");
        scanf("%d", &escolha);

        if (escolha == 1)
        {

            inserir_cliente();
            break;
            fflush(stdin);
        }
        else if (escolha != 2)
        {
            system("CLS");
            printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
            fflush(stdin);
        }

    } while (escolha != 2);

    system("CLS");
    printf("* Cliente inserido com sucesso *\n");
}

void pesquisar_cliente() // Feito 100 não mexer mais
{
    struct dadoscliente clientes;
    int clienteEncontrado = 0;
    int geral; // Códico reutilizado nas variáveis NIF e Telefone;
    int escolha;
    char line[256];

    FILE *dados = fopen("InfoClientes.txt", "r"); // Read only
    if (dados == NULL)
    {
        printf("Arquivo não encontrado\n");
        exit(-1);
    };
    system("CLS");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("* Pesquisar Cliente *\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Como pretende pesquisar pelo cliente?\n");
    printf("1- NIF\n");
    printf("2- Telefone\n");
    printf("R:");
    scanf("%d", &geral);

    if (geral == 1) // se escolher apção 1 compara o nif que foi introduzido com o nif no txt.
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar Cliente *\n");
        printf("---------------------------------------------------------------------------------------------\n");

        printf("Introduza o NIF:");
        scanf("%d", &geral);
        while (fgets(line, sizeof(line), dados))
        {
            sscanf(line, "Nome: %[^\n]", clientes.nome);
            sscanf(line, "Morada: %[^\n]", clientes.morada);
            sscanf(line, "Telefone: %d", &clientes.telefone);
            sscanf(line, "Nif: %d", &clientes.nif);

            if (geral == clientes.nif)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do cliente:\n");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Nome:%s\n", clientes.nome);
                printf("Morada:%s\n", clientes.morada);
                printf("Telefone:%d\n", clientes.telefone);
                printf("NIF:%d\n", clientes.nif);

                clienteEncontrado = 1;
                break;
            }
        }
    }
    else if (geral == 2) // se escolher apção 2 compara o telefone que foi introduzido com o telefone no txt.
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar Cliente *\n");
        printf("---------------------------------------------------------------------------------------------\n");

        printf("Introduza o número de Telefone:");
        scanf("%d", &geral);
        while (fgets(line, sizeof(line), dados))
        {
            sscanf(line, "Nome: %[^\n]", clientes.nome);
            sscanf(line, "Morada: %[^\n]", clientes.morada);
            sscanf(line, "Telefone: %d", &clientes.telefone);
            sscanf(line, "Nif: %d", &clientes.nif);

            if (geral == clientes.telefone)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do cliente:\n");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Nome:%s\n", clientes.nome);
                printf("Morada:%s\n", clientes.morada);
                printf("Telefone:%d\n", clientes.telefone);
                printf("NIF:%d\n", clientes.nif);

                clienteEncontrado = 1;

                break;
            }
        }
    }

    if (clienteEncontrado != 1) // caso o NIF ou Telefone introduzido não sejam compativeis com os no txt informa e volta a realizar o ciclo.
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("Valor inserido não encontrado: %d\n", geral);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    fclose(dados);

    fflush(stdin);
    do
    {
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("Pretende pesquisar mais algum cliente?\n");
        printf("1- Sim\n");
        printf("2- Não\n");
        printf("R:");
        scanf("%d", &escolha);

        if (escolha == 1)
        {

            pesquisar_cliente();
            break;
            fflush(stdin);
        }
        else if (escolha != 2)
        {
            fflush(stdin);
            system("CLS");
            printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
        }

    } while (escolha != 2);

    system("CLS");
    printf("* Saiu da pesquisa do cliente *\n");
}

void inserir_produto() // Feito 100 não mexer mais
{
    FILE *dados;
    struct dadosprodutos produto;

    int contador = carregar_contador(); // Função para puxar o contador
    int escolha;

    dados = fopen("InfoProdutos.txt", "a");

    if (dados == 0)
    {
        printf("*ERROR*\n");
        printf("Arquivo não encontrado");
    }
    else
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Inserir dados do produto *\n");
        printf("---------------------------------------------------------------------------------------------\n");
        fflush(stdin);
        printf("Digite o nome do produto:");
        fgets(produto.nome, sizeof(produto.nome), stdin);
        fflush(stdin);
        printf("Digite o preço do produto:");
        scanf("%f", &produto.preco);
        printf("Digite o stock do produto:");
        scanf("%d", &produto.stock);

        contador++;

        salvar_contador(contador);

        produto.num = contador;

        fprintf(dados, "\nProduto:\n");
        fprintf(dados, "Nome: %s", produto.nome); // Como utilizamos fgets nao podemos usar /n
        fprintf(dados, "Preço: %.2f€\n", produto.preco);
        fprintf(dados, "Stock: %d \n", produto.stock);
        fprintf(dados, "Número do produto: %d \n", produto.num);

        fclose(dados);

        fflush(stdin);
        do
        {
            printf("\n---------------------------------------------------------------------------------------------\n");
            printf("Pretende inserir mais algum produto?\n");
            printf("1- Sim\n");
            printf("2- Não\n");
            printf("R:");
            scanf("%d", &escolha);

            if (escolha == 1)
            {

                inserir_produto();
                break;
                fflush(stdin);
            }
            else if (escolha != 2)
            {
                fflush(stdin);
                system("CLS");
                printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
            }

        } while (escolha != 2);

        system("CLS");
        printf("* Produto inserido com sucesso *\n");
    }
}

void pesquisar_produto() // Feito 100 não mexer mais
{
    struct dadosprodutos produtos;
    char data[256];
    int produto_encontrado = 0;
    int escolha;
    int num1;

    FILE *dados2 = fopen("InfoProdutos.txt", "r");
    if (dados2 == NULL)
    {
        printf("Oops, file can't be read \n");
        exit(-1);
    }

    system("CLS");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("* Pesquisar Produto *\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Como pretende pesquisar pelo produto?\n");
    printf("1- Stock do produto\n");
    printf("2- Número do produto\n");
    printf("R:");
    scanf("%d", &escolha);

    getchar();

    if (escolha == 1)

    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar produto *\n");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("Introduza o stock do produto:");
        scanf("%d", &num1);

        while (fgets(data, sizeof(data), dados2))
        {
            sscanf(data, "Nome: %s", produtos.nome);
            sscanf(data, "Preço: %f", &produtos.preco);
            sscanf(data, "Stock: %d", &produtos.stock);
            sscanf(data, "Número do produto: %d", &produtos.num);

            if (produtos.stock == num1)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do produto:\n");
                printf("---------------------------------------------------------------------------------------------\n");

                printf("Nome:%s\n", produtos.nome);
                printf("Preço:%.2f\n", produtos.preco);
                printf("Stock:%d\n", produtos.stock);
                printf("Número:%d\n", produtos.num);

                produto_encontrado = 1;
                break;

                fclose(dados2);
            }
        }
    }
    else if (escolha == 2)
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar produto *\n");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("Introduza o número do produto:");
        scanf("%d", &num1);

        while (fgets(data, sizeof(data), dados2))
        {
            sscanf(data, "Nome: %s", produtos.nome);
            sscanf(data, "Preço: %f", &produtos.preco);
            sscanf(data, "Stock: %d", &produtos.stock);
            sscanf(data, "Número do produto: %d", &produtos.num);

            if (produtos.num == num1)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do produto:\n");
                printf("---------------------------------------------------------------------------------------------\n");

                printf("Nome:%s\n", produtos.nome);
                printf("Preço:%.2f\n", produtos.preco);
                printf("Stock:%d\n", produtos.stock);
                printf("Número:%d\n", produtos.num);

                produto_encontrado = 1;
                break;

                fclose(dados2);
            }
        }
    }

    if (produto_encontrado == 0)
    {
        system("CLS");
        printf("* Produto não encontrado *\n");
    }

    do
    {
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("Pretende pesquisar mais algum produto?\n");
        printf("1- Sim\n");
        printf("2- Não\n");
        printf("R:");
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            pesquisar_produto();
            break;
        }
        else if (escolha != 2)
        {
            system("CLS");
            printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
        }

    } while (escolha != 2);

    system("CLS");
    printf("* Saiu da pesquisa do produto *\n");
}

void editar_cliente(struct dadoscliente *cliente)
{
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("Editar cliente:\n");
    printf("---------------------------------------------------------------------------------------------\n");

    printf("Novo Nome: ");
    scanf(" %[^\n]", cliente->nome);

    printf("Nova Morada: ");
    scanf(" %[^\n]", cliente->morada);

    printf("Novo Telefone: ");
    scanf("%d", &cliente->telefone);

    // Não é permitido alterar o NIF

    printf("\nCliente editado com sucesso!\n");
}

void pesquisar_clienteEditar()
{
    struct dadoscliente clientes;
    int clienteEncontrado = 0;
    int geral;
    int escolha;

    FILE *dados = fopen("InfoClientes.txt", "r+");
    if (dados == NULL)
    {
        printf("Arquivo não encontrado\n");
        exit(-1);
    }

    FILE *temporario = fopen("temp.txt", "w");
    if (temporario == NULL)
    {
        printf("Erro ao criar arquivo temporário\n");
        fclose(dados);
        exit(-1);
    }

    system("CLS");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("* Pesquisar Cliente *\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Como pretende pesquisar pelo cliente?\n");
    printf("1- NIF\n");
    printf("2- Telefone\n");
    printf("R:");
    scanf("%d", &geral);

    if (geral == 1)
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar Cliente *\n");
        printf("---------------------------------------------------------------------------------------------\n");

        printf("Introduza o NIF:");
        scanf("%d", &geral);

        while (fscanf(dados, "Cliente:\nNome: %[^\n]\nMorada: %[^\n]\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, &clientes.telefone, &clientes.nif) == 4)
        {
            if (geral == clientes.nif)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do cliente:\n");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Nome:%s\n", clientes.nome);
                printf("Morada:%s\n", clientes.morada);
                printf("Telefone:%d\n", clientes.telefone);
                printf("NIF:%d\n", clientes.nif);

                clienteEncontrado = 1;

                do
                {
                    printf("---------------------------------------------------------------------------------------------\n");
                    printf("O que pretende fazer?\n");
                    printf("1- Editar cliente\n");
                    printf("2- Apagar Cliente /  Sair\n");
                    printf("R:");
                    scanf("%d", &escolha);

                    switch (escolha)
                    {
                    case 1:
                        editar_cliente(&clientes);
                        fprintf(temporario, "Cliente:\nNome: %s\nMorada: %s\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, clientes.telefone, clientes.nif);
                        break;
                    case 2:
                        printf("A sair...\n");
                        break;
                    default:
                        printf("Escolha inválida. Por favor, escolha 1, 2 ou 3.\n");
                    }
                } while (escolha != 2);

                system("CLS");
            }
            else
            {
                fprintf(temporario, "Cliente:\nNome: %s\nMorada: %s\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, clientes.telefone, clientes.nif);
            }
        }
    }
    else if (geral == 2)
    {
        system("CLS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Pesquisar Cliente *\n");
        printf("---------------------------------------------------------------------------------------------\n");

        printf("Introduza o número de Telefone:");
        scanf("%d", &geral);

        while (fscanf(dados, "Cliente:\nNome: %[^\n]\nMorada: %[^\n]\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, &clientes.telefone, &clientes.nif) == 4)
        {
            if (geral == clientes.telefone)
            {
                system("CLS");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Informações do cliente:\n");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("Nome:%s\n", clientes.nome);
                printf("Morada:%s\n", clientes.morada);
                printf("Telefone:%d\n", clientes.telefone);
                printf("NIF:%d\n", clientes.nif);

                clienteEncontrado = 1;

                do
                {
                    printf("---------------------------------------------------------------------------------------------\n");
                    printf("O que pretende fazer?\n");
                    printf("1- Editar cliente\n");
                    printf("2- Apagar Cliente /  Sair\n");
                    printf("R:");
                    scanf("%d", &escolha);

                    switch (escolha)
                    {
                    case 1:
                        editar_cliente(&clientes);
                        fprintf(temporario, "Cliente:\nNome: %s\nMorada: %s\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, clientes.telefone, clientes.nif);
                        break;
                    case 2:
                        printf("A sair...\n");
                        break;
                    default:
                        printf("Escolha inválida. Por favor, escolha 1, 2 ou 3.\n");
                    }
                } while (escolha != 2);

                system("CLS");
            }
            else
            {
                fprintf(temporario, "Cliente:\nNome: %s\nMorada: %s\nTelefone: %d\nNif: %d\n\n", clientes.nome, clientes.morada, clientes.telefone, clientes.nif);
            }
        }
    }

    fclose(dados);
    fclose(temporario);

    remove("InfoClientes.txt");
    rename("temp.txt", "InfoClientes.txt");

    if (clienteEncontrado != 1)
    {
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("Valor inserido não encontrado: %d\n", geral);
        printf("Pressione qualquer tecla para continuar...");
        getchar();
        getchar();
        system("CLS");
    }
}

void editar_produto(struct dadosprodutos *produto)
{
    char novo_nome[256];
    printf("Novo nome do produto: ");
    fflush(stdin);
    fgets(novo_nome, sizeof(novo_nome), stdin);
    sscanf(novo_nome, "%[^\n]", produto->nome);
    printf("Novo preço do produto: ");
    scanf("%f", &produto->preco);
    printf("Novo stock do produto: ");
    scanf("%d", &produto->stock);
}

void pesquisar_produtoEditar()
{
    struct dadosprodutos produtos;
    int produto_encontrado = 0;
    int escolha;
    int num1;
    char line[256];

    FILE *dados2 = fopen("InfoProdutos.txt", "r+");
    FILE *temporario = fopen("temporario.txt", "w");

    if (dados2 == NULL || temporario == NULL)
    {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    system("CLS");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("* Pesquisar produto *\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Introduza o número do produto:");
    scanf("%d", &num1);

    while (fgets(line, sizeof(line), dados2))
    {
        sscanf(line, "Nome: %s", produtos.nome);
        sscanf(line, "Preço: %f", &produtos.preco);
        sscanf(line, "Stock: %d", &produtos.stock);
        sscanf(line, "Número do produto: %d", &produtos.num);

        if (produtos.num == num1)
        {
            system("CLS");
            printf("---------------------------------------------------------------------------------------------\n");
            printf("Informações do produto:\n");
            printf("---------------------------------------------------------------------------------------------\n");

            printf("Nome:%s\n", produtos.nome);
            printf("Preço:%.2f\n", produtos.preco);
            printf("Stock:%d\n", produtos.stock);
            printf("Número:%d\n", produtos.num);

            produto_encontrado = 1;
            break;
        }
    }

    if (produto_encontrado)
    {
        do
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("O que pretende fazer?\n");
            printf("1- Editar produto\n");
            printf("2- Apagar Produto / Sair\n");
            printf("R: ");
            scanf("%d", &escolha);

            switch (escolha)
            {
            case 1:
                editar_produto(&produtos);
                fprintf(temporario, "Nome: %s\nPreco: %.2f\nStock: %d\nNum: %d\n\n", produtos.nome, produtos.preco, produtos.stock, produtos.num);
                break;
            case 2:
                system("CLS");
                printf("A sair...\n");
                break;
            default:
                printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
            }
        } while (escolha != 2);

        printf("---------------------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("* Produto não encontrado *\n");
    }

    fclose(dados2);
    fclose(temporario);
}

void inserir_venda_preco()
{
    int nifCliente;
    int opcaoProduto;
    int quantidade;
    char continuar;
    float precoTotal = 0;

    Produto produtos[] = {
        {1, "Batatas 10 KG", 10.99, 20},
        {2, "Arroz 1KG", 2.49, 15},
        {3, "Nestum", 3.50, 30},
        {4, "Cerelac", 4, 15},
        {5, "Sardinhas 1KG", 8.79, 12},
        {6, "Carne Picada 1KG", 5.60, 10},
    };

    int numProdutos = sizeof(produtos) / sizeof(produtos[0]);

    system("CLS");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("* Inserir Venda *\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // Solicitar NIF do cliente com verificação de 9 dígitos
    do
    {
        printf("Digite o NIF do cliente (9 dígitos): ");
        scanf("%9d", &nifCliente);

        if (nifCliente < 100000000 || nifCliente > 999999999)
        {
            printf("NIF inválido. Deve ter exatamente 9 dígitos.\n");
        }

    } while (nifCliente < 100000000 || nifCliente > 999999999);

    do
    {
        // Mostrar produtos disponíveis
        printf("\nProdutos disponiveis:\n");
        for (int i = 0; i < numProdutos; i++)
        {
            printf("%d. %s - %.2f euros (Estoque: %d)\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
        }

        printf("\nEscolha um produto (digite o codigo): ");
        scanf("%d", &opcaoProduto);

        if (opcaoProduto < 1 || opcaoProduto > numProdutos)
        {
            printf("Opcao invalida.\n");
            continue;
        }

        printf("Digite a quantidade desejada: ");
        scanf("%d", &quantidade);

        if (quantidade > produtos[opcaoProduto - 1].estoque)
        {
            printf("Estoque insuficiente para a quantidade desejada.\n");
            continue;
        }

        float total = produtos[opcaoProduto - 1].preco * quantidade;
        produtos[opcaoProduto - 1].estoque -= quantidade;

        precoTotal += total;

        char dataAtual[20];
        obterDataAtual(dataAtual);

        FILE *faturaFile = fopen("HistoricoVendas.txt", "a");
        if (faturaFile == NULL)
        {
            printf("Erro ao criar/abrir o arquivo de fatura.\n");
            return;
        }

        fprintf(faturaFile, "Data: %s\n", dataAtual);
        fprintf(faturaFile, "NIF do cliente: %d\n", nifCliente);
        fprintf(faturaFile, "Produto: %s\n", produtos[opcaoProduto - 1].nome);
        fprintf(faturaFile, "Quantidade: %d\n", quantidade);
        fprintf(faturaFile, "Total: %.2f euros\n", total);
        fprintf(faturaFile, "-----------------------\n");

        fclose(faturaFile);

        printf("Deseja adicionar mais produtos? (S para Sim, qualquer tecla para Nao): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    system("CLS");
    printf("O valor da sua compra ficou em %.2f euros\n", precoTotal);
    printf("Compra realizada com sucesso. Fatura gravada em 'HistoricoVendas.txt'.\n");
}

void historico_cliente()
{
    int esc;

    FILE *faturaFile = fopen("HistoricoVendas.txt", "r");

    if (faturaFile == NULL)
    {
        printf("Erro ao abrir o arquivo de fatura.\n");
        return;
    }

    char linha[100]; // Ajuste o tamanho conforme necessário
    system("CLS");
    printf("-----------------------\n");
    printf("* Histórico de Vendas *\n");
    printf("-----------------------\n");

    // Ler e imprimir cada linha do arquivo
    while (fgets(linha, sizeof(linha), faturaFile) != NULL)
    {
        printf("%s", linha);
    }

    do
    {
        if (esc != 1)
        {
            printf("Press 1 for exit\n");
        }
        scanf("%d", &esc);

    } while (esc != 1);

    system("CLS");

    fclose(faturaFile);
}

int main() // Feito // Menu e todas as opções
{

    int esc;

    do
    {
        printf("---------------------------------------------------------------------------------------------\n");
        printf("* Gestão de Loja *\n");
        printf("---------------------------------------------------------------------------------------------\n");

        printf("1- Inserir cliente\t\t");

        printf("2- Inserir produto\t\t");

        printf("3- Pesquisar cliente\n");

        printf("4- Pesquisar produto\t\t");

        printf("5- Editar cliente\t\t"); // Aqui podemos tbm apagar o cliente

        printf("6- Editar produto\n"); // Aqui podemos tbm apagar o produto

        printf("7- Inserir venda\t\t");

        printf("8- Ver Fatura\t\t\t"); // Fatura = histórico

        printf("0- Fechar o programa\n");

        printf("---------------------------------------------------------------------------------------------\n");

        printf("Digite a sua opção:");
        scanf("%d", &esc);

        switch (esc)
        {
        case 1:
            inserir_cliente();
            break;
        case 2:
            inserir_produto();
            break;
        case 3:
            pesquisar_cliente();
            break;
        case 4:
            pesquisar_produto();
        case 5:
            pesquisar_clienteEditar();
            break;
        case 6:
            pesquisar_produtoEditar();
            break;
        case 7:
            inserir_venda_preco();
            break;
        case 8:
            historico_cliente();
            break;
        default:
            break;
        }

    } while (esc != 0);

    system("CLS");
    printf("* Saiu do programa *");
}