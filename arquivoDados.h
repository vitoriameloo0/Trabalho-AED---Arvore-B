#ifndef ARQUIVODADOS_H
#define ARQUIVODADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "arquivo.h"
#include "arquivoIndice.h"

#define MAXX 51
#define MAXY 41
#define MAX 100

typedef struct Produto{
    int codigo;
    char nomeProduto[MAXX];
    char marca[MAXY];
    char categoriaProduto[MAXX];
    int estoque;
    float valorProduto;
} Produto;

typedef struct cab_Dados{
    int pos_livre; // inicio da lista de nos livre
    int pos_topo; //  primeira posicao nao usada do inicio da lista
} cab_Dados;

// Funcao para le o cabeçalho do arquivo binario
// Entrada: Arquivo Binario
// Retorno: Ponteiro do cabeçalho
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Cabeçalho do arquivo retornado
cab_Dados* le_cabecalho(FILE *arq);

// Função para escrever os dados do cabeçalho no arquivo
// Entrada: Arquivo binario e ponteiro do dados do cabeçalho pra gravar
// Retorno: Nenhuma
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Escrita do dado no arquivo binario
void escrever_cabecalho(FILE* arq, cab_Dados* cab);

// Função para le os dados do produto em uma determinada posicao do arquivo
// Entrada: Arquivo binario e posicao do produto
// Retorno: Ponteiro do Produto
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: No do produto retornado
Produto* le_no(FILE* arq, int pos);

// Funcao para escrever no arquivo binario os dados do produto em uma determinada posicao
// Entrada: Arquivo Binario, o produto e a posicao
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Dados escrito no arquivo binario
void escreve_no(FILE* arq, Produto* x, int pos);

// Função para inserir os dados do produto no arquivo binario em uma determinada posicao
// Entrada: Arquivo binario, no com as informaçoes do produto e a posicao
// Retorno: Posicao em que os dados foram inserido no arquivo
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Produtos inserido no arquivo
int insercaoArqDados(FILE* arq, Produto* info, int pos);

// Funcao para fazer o cadastro de forma manual do produto
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feito o cadastro de um produto
void cadastro(FILE* arqDados, FILE* arqIndice);

// Funcao Auxiliar para imprimir as posiçoes livre do arquivo de dados
// Entrada: Arquivo de dados e posicao
// Retorno: Nenhum
// Pre-Condicao: Nenhum
// Pos-Condicao: Nenhum
void imprimirLivreAuxD(FILE* arq, int posicao);

// Função para imprimir as posições livres do arquivo de Dados
// Entrada: Arquivo de dados
// Retorno: Nenhum
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivreDados(FILE* arq);

// Função para imprimir um produto de acordo com seu codigo
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Produto imprimido
void imprimirProduto(FILE* arqDados, FILE* arqIndice);

// Função para atualizar o estoque de um produto
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Estoque do produto atualizado
void atualizarEstoque(FILE* arqDados, FILE* arqIndice);

// Função para atualizar o valor de um produto
// Entrada: Arquivo de dados e Arquivo de indice
// Retorno: Nenhum
// Pre-Condicao: Produto esta cadastrado
// Pos-Condicao: Preco do produto atualizado
void atualizarValor (FILE* arqDados, FILE* arqIndice);

// Funçao para remover do arquivo de dados um produto
// Entrada: Arquivo de dados
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e produto esta cadastrado
// Pos-Condicao: Produto removido
void removerDados(FILE* arq, int posicao);


#endif //ARQUIVODADOS_H
