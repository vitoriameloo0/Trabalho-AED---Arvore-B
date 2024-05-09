#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "arquivo.h"
#include "arquivoDados.h"
#include "arquivoIndice.h"

#define MAXX 51
#define MAXY 41
#define MAX 100

// Mostra o menu de opcoes do programa
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Nenhuma
void menu(FILE* arqDados, FILE* arqIndice){
    int codigo;
    char str[MAX];

    while(1){
        printf("\n------------- MENU ---------------------\n");
        printf("1 - Cadastrar\n");
        printf("2 - Imprimir\n");
        printf("3 - Remover\n");
        printf("4 - Atualizar\n");
        printf("5 - Inclusao em lote\n");
        printf("0 - Sair do programa\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao do menu: ");
        scanf("%[^\n]%*c", str);
        codigo = (strpbrk(str, "012345") == NULL)? 9 : atoi(str);
        printf("\n");

        switch(codigo){
            case 1:
                cadastrarProduto(arqDados, arqIndice);
                break;
            case 2:
                imprimir(arqDados, arqIndice);
                break;
            case 3:
                remover(arqDados, arqIndice);
                break;
            case 4:
                atualizar(arqDados, arqIndice);
                break;
            case 5:
                loadPath(arqDados, arqIndice);
                break;
            case 0:
                return;
            default:
                printf("Opcao Invalida.\n");
        }
    }
}

// Mostra o menu de impressoes que podem ser feitas
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Executa a funcao escolhida
void imprimir(FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo;
    printf("\n--------------- IMPRIMIR ------------------\n");
    printf("1  - Imprimir Produto\n");
    printf("2  - Imprimir Produtos InOrdem\n");
    printf("3  - Imprimir Arvore\n");
    printf("4  - Imprimir Lista de Livres do Arquivo de Indice\n");
    printf("5  - Imprimir Lista de Livres do Arquivo de Dados\n");

    printf("Escolha uma opcao de impressao: ");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);
    printf("\n");

    switch(codigo){
        case 1:
            imprimirProduto(arqDados, arqIndice);
            break;
        case 2:
            imprimirInOrdem(arqIndice, arqDados);
            break;
        case 3:
            imprimirArvore(arqIndice);
            break;
        case 4:
            imprimirLivresIndice(arqIndice);
            break;
        case 5:
            imprimirLivreDados(arqDados);
            break;
        default:
            printf("Opcao Invalida.\n");
    }
}

// Mostra o menu de remocao que podem ser feitas
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feita a remocao de um produto
void remover(FILE* arqDados, FILE* arqIndice){
    int codigo, posicao;
    char str[MAX];

    printf("\n--------------- REMOVER ----------------\n");
    printf("\nDigite o codigo do produto que deseja remover: \n");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);

    posicao = removerArvore(arqIndice, codigo);
    if(posicao != -1)
        removerDados(arqDados, posicao);

    printf("-------------------------------------------\n");
    printf("Produto Removido\n\n");
}

// Mostra o menu de atualizaçao que podem ser feitas no produto
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feita a atualização da opção escolhida
void atualizar(FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo;
    printf("\n-------------- ATUALIZAR ---------------\n");
    printf("O que deseja atualizar: \n");
    printf("1 - Atualizar Estoque\n");
    printf("2 - Atualizar Valor do Produto\n");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);

    switch(codigo){
        case 1:
            atualizarEstoque(arqDados, arqIndice);
            break;

        case 2:
            atualizarValor(arqDados, arqIndice);
            break;

        default:
            printf("Opcao Invalida.\n");
            return;
    }
    printf("-------------------------------------------\n");
}

