#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arquivo.h"
#include "arquivoDados.h"
#include "arquivoIndice.h"

// Funcao para le o cabeçalho do arquivo binario
// Entrada: Arquivo Binario
// Retorno: Ponteiro do cabeçalho
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Cabeçalho do arquivo retornado
cab_Dados* le_cabecalho(FILE *arq){
    cab_Dados *cab = (cab_Dados*)malloc(sizeof(cab_Dados));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cab_Dados), 1, arq);
    return cab;
}

// Função para escrever os dados do cabeçalho no arquivo
// Entrada: Arquivo binario e ponteiro do dados do cabeçalho pra gravar
// Retorno: Nenhuma
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Escrita do dado no arquivo binario
void escrever_cabecalho(FILE* arq, cab_Dados* cab){
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cab_Dados), 1, arq);
}

// Função para le os dados do produto em uma determinada posicao do arquivo
// Entrada: Arquivo binario e posicao do produto
// Retorno: Ponteiro do Produto
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: No do produto retornado
Produto* le_no(FILE* arq, int pos){
    Produto* x = (Produto*) malloc(sizeof(Produto));
    fseek(arq, sizeof(cab_Dados)+ pos*sizeof(Produto), SEEK_SET);
    fread(x, sizeof(Produto), 1, arq);
    return x;
}

// Funcao para escrever no arquivo binario os dados do produto em uma determinada posicao
// Entrada: Arquivo Binario, o produto e a posicao
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Dados escrito no arquivo binario
void escreve_no(FILE* arq, Produto* x, int pos){
    fseek(arq, sizeof(cab_Dados)+ pos*sizeof(Produto), SEEK_SET);
    fwrite(x, sizeof(Produto), 1, arq);
}

// Função para inserir os dados do produto no arquivo binario em uma determinada posicao
// Entrada: Arquivo binario, no com as informaçoes do produto e a posicao
// Retorno: Posicao em que os dados foram inserido no arquivo
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Produtos inserido no arquivo
int insercaoArqDados(FILE* arq, Produto* info, int posicao){
    int pos_escrita;
    if(posicao == -1){ // Caso insira um dado novo ou em uma posicao livre
        cab_Dados* cab = le_cabecalho(arq);

        if(cab->pos_livre == -1){ // Caso não tenha posicao livre

            escreve_no(arq, info , cab->pos_topo);
            pos_escrita = cab->pos_topo;
            cab->pos_topo++;
        }
        else{ // Caso tenha posicao livre
            int pos_aux;
            Produto* aux = le_no(arq, cab->pos_livre);

            pos_aux = cab->pos_livre;
            cab->pos_livre = aux->codigo;

            escreve_no(arq, info, pos_aux);
            pos_escrita = pos_aux;
            free(aux);
        }
        escrever_cabecalho(arq, cab);
        free(cab);
    }
    else{ // Caso faca uma alteracao no estoque ou valor
        escreve_no(arq, info, posicao);
        pos_escrita = posicao;
    }
    return pos_escrita;
}

// Funcao para fazer o cadastro de forma manual do produto
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feito o cadastro de um produto
void cadastrarProduto(FILE* arqDados, FILE* arqIndice){
    int codigo, estoque, real, centavos, posicao, pos;
    char str[MAX], nome[MAXX], marca[MAXY], categoria[MAXX];

    printf("\n--------------- CADASTRAR ---------------\n");
    printf("\nCodigo do Produto: ");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);

    pos = buscarDados(arqIndice, codigo);
    if(pos != -1){
        printf("Produto ja esta cadastrado\n");
        return;
    }
    else{
        printf("Nome do Produto: ");
        scanf("%[^\n]%*c", nome);

        printf("Nome da Marca: ");
        scanf("%[^\n]%*c", marca);

        printf("Nome da Categoria do Produto: ");
        scanf("%[^\n]%*c", categoria);

        printf("Quantidade em Estoque: ");
        scanf("%[^\n]%*c", str);
        estoque = atoi(str);

        printf("Valor do Produto: ");
        scanf("%[^\n]%*c", str);
        real = atoi(str);
        centavos = (strpbrk(str, ",.") == NULL) ? 0 : atoi(strpbrk(str, ",.")+1);

        Produto* p = (Produto*) malloc(sizeof(Produto));
        p->codigo = codigo;
        strcpy(p->nomeProduto, nome);
        strcpy(p->marca, marca);
        strcpy(p->categoriaProduto, categoria);
        p->estoque = estoque;
        p->valorProduto = real+centavos/100.0;

        posicao = insercaoArqDados(arqDados, p, -1);
        inserirArvore(arqIndice, codigo, posicao);
        printf("-----------------------------------------\n");
        printf("Produto Cadastrado com Sucesso\n\n");
    }
}

// Funcao Auxiliar para imprimir as posiçoes livre do arquivo de dados
// Entrada: Arquivo de dados e posicao
// Retorno: Nenhum
// Pre-Condicao: Nenhum
// Pos-Condicao: Nenhum
void imprimirLivreAuxD(FILE* arq, int posicao){
    if(posicao == -1) return;

    printf("%d ", posicao);
    Produto* aux =  le_no(arq, posicao);
    int prox = aux->codigo;
    free(aux);
    imprimirLivreAuxD(arq, prox);
}

// Função para imprimir as posições livres do arquivo de Dados
// Entrada: Arquivo de dados
// Retorno: Nenhum
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivreDados(FILE* arq){
    cab_Dados* cab = le_cabecalho(arq);
    int posLivre = cab->pos_livre;

    printf("Posicoes Livres: \n");
    imprimirLivreAuxD(arq, posLivre);
    printf("\n");
}

// Função para imprimir um produto de acordo com seu codigo
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Produto imprimido
void imprimirProduto(FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo, posicao;

    printf("Digite o codigo do produto: ");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);
    posicao = buscarDados(arqIndice, codigo);

    if(posicao != -1){
        Produto* p = le_no(arqDados, posicao);
        printf("\nCodigo do Produto: %d\n", p->codigo);
        printf("Nome do Produto: %s\n", p->nomeProduto);
        printf("Marca: %s\n", p->marca);
        printf("Categoria: %s\n", p->categoriaProduto);
        printf("Estoque: %d\n", p->estoque);
        printf("Valor: R$%.2f\n", p->valorProduto);
    }
    else
        printf("Produto nao esta cadastrado\n\n");
}

// Função para atualizar o estoque de um produto
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Estoque do produto atualizado
void atualizarEstoque(FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo, estoque, pos;
    Produto* p;

    printf("Digite o codigo do produto a ser atualizado: ");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);

    pos = buscarDados(arqIndice, codigo);
    if(pos == -1){
        printf("Produto nao esta cadastrado\n");
        return;
    }

    p = le_no(arqDados, pos);

    printf("Insira o novo valor do estoque: ");
    scanf("%[^\n]%*c", str);
    estoque = atoi(str);

    p->estoque = estoque;
    insercaoArqDados(arqDados, p, pos);
    free(p);
}

// Função para atualizar o valor de um produto
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Preco do produto atualizado
void atualizarValor (FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo, estoque, real, centavo, pos;
    Produto* p;
    printf("Insira o codigo a ser atualizado: ");
    scanf("%[^\n]%*c", str);
    codigo = atoi(str);

    pos = buscarDados(arqIndice, codigo);

    if(pos == -1){
        printf("Produto nao esta cadastrado\n");
        return;
    }

    p = le_no(arqDados, pos);
    printf("Insira o novo valor do produto: ");
    scanf("%[^\n]%*c", str);
    real = atoi(str);
    centavo = (strpbrk(str, ",.")==NULL) ? 0 : atoi(strpbrk(str, ",.")+1);

    p->valorProduto = real+centavo/100.0;
    insercaoArqDados(arqDados, p, pos);
    free(p);
}

// Funçao para remover do arquivo de dados um produto
// Entrada: Arquivo de dados
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e produto esta cadastrado
// Pos-Condicao: Produto removido
void removerDados(FILE* arq, int posicao){
    Produto* aux = le_no(arq, posicao);
    cab_Dados* cab = le_cabecalho(arq);

    aux->codigo = cab->pos_livre;
    cab->pos_livre = posicao;
    escrever_cabecalho(arq, cab);
    insercaoArqDados(arq, aux, posicao);
    free(cab);
    free(aux);
}


