#ifndef ARQUIVOINDICE_H
#define ARQUIVOINDICE_H

#include <stdio.h>
#include "arquivoDados.h"

#define ORDEM 5

typedef struct no{
    int numChaves;
    int chaves[ORDEM];
    int ptDados[ORDEM];
    int filhos[ORDEM + 1]
}arvoreB; //Struct com as informações da arvore

typedef struct cab_Indice{
    int raiz;
    int topo;
    int livre;
}cab_Indice; //Struct com as informações do cabeçalho do arquivo de indice

typedef struct lista{
    int andar;
    int n;
    int v[ORDEM];
    struct lista*prox;
}lista;

// Função para escrever os dados do cabeçalho no arquivo
// Entrada: Arquivo binario e ponteiro do dados do cabeçalho pra gravar
// Retorno: Nenhuma
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Escrita do dado no arquivo binario
void escrever_cabecalhoIndice(FILE* arq, cab_Indice* cab);

// Funcao para le o cabeçalho do arquivo binario
// Entrada: Arquivo Binario
// Retorno: Ponteiro do cabeçalho
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Cabeçalho do arquivo retornado
cab_Indice* le_cabecalhoIndice(FILE* arq);

// Função para le os dados do produto em uma determinada posicao do arquivo
// Entrada: Arquivo binario e posicao do produto
// Retorno: Ponteiro do Produto
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: No do produto retornado
arvoreB* le_noArvore(FILE* arq, int posicao);

// Funcao para escrever no arquivo binario os codigo do produto e suas informaçoes
// Entrada: Arquivo Binario, o produto e a posicao
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Dados escrito no arquivo binario
void escreve_noArvore(FILE* arq, arvoreB* x, int posicao);

// Função para inserir os codigos dos produto no arquivo binario em uma determinada posicao
// Entrada: Arquivo binario com as informações, arvore com os dados e a posiçao do dado no arquivo de dado
// Retorno: Posicao em que os dados foram inserido no arquivo de indice
// Pre-Condicao: Ter inserido os dados no arquivo de dados
// Pos-Condicao: Codigo e suas informações inserido no arquivo
int insercaoArqIndice(FILE* arq, arvoreB* x, int posicao);

// Função para fazer a copia dos dados do vetor v1 para v
// Entrada: Vetores v e v1, e o tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados copiados
void copiarVetor(int v[], int v1[], int n);

// Função para imprimir os dados de um vetor
// Entrada: Vetores v e o tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados imprimido
void imprimirVetor(int v[], int n);

// Função para inserir os dados na lista do arquivo de indice, encadeando as informaçoes inseridas
// Entrada: Lista, andar, vetor e o tamanho
// Saida: Lista
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados copiados
lista* inserirLista(lista* l, int andar, int v[], int n);

// Função auxiliar para imprimir as posições livres de forma recursiva do arquivo de indice
// Entrada: arquivo de indice, primeira posicao livre
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivresIndiceAUX(FILE* arq, int pos);

// Função para imprimir as posições livres arquivo de indice
// Entrada: arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivresIndice(FILE* arq);

// Função para percorrer a arvore pelo arquivo de indice
// Entrada: Arquivo de indice, posicao da raiz, inicio da lista e o andar inicial
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Arvore percorrida
void percorrerArvore(FILE* f, int pos, lista** l, int andar);

// Função para imprimir a lista de dados que estão em um vetor
// Entrada: Arquivo de indice, posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLista(lista* l, int andar);

// Função para imprimir os valores que estao na arvore em cada andar
// Entrada: Arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirArvore(FILE* arq);

// Função auxiliar para imprimir os codigos em ordem crescente
// Entrada: Arquivo de indice e posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirInOrdemAUX(FILE* arq, int pos);

// Função para imprimir a lista de dados em ordem crescente
// Entrada: Arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Valores impresso
void imprimirInOrdem(FILE* arq);

// Função para inserir as chaves
// Entrada: Vetor de chave, tamanho e o codigo
// Saida: Posicao que a chav
// Pre-Condicao: Nenhuma
// Pos-Condicao: Chave inserida e devolução de sua posicao no arquivo
int inserirChave(int v[], int n, int codigo);

// Função para inserir a posicao do produto no arquivo de dados no arquivo de indice
// Entrada: Vetor de PtDados, posicao no arqIndice, posicao do arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: PtDado inserida e devolução de sua posicao no arquivo
void inserirPT(int v[], int n, int posicao, int pos);

// Função para puxar os dados de um vetor para fechar um espaço
// Entrada: Vetor de chave, tamanho e o posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void puxar(int v[], int n, int pos);

// Função para empurrar os dados de um vetor para abrir um espaço
// Entrada: Vetor de chave, tamanho e o posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void empurrar(int v[], int n, int pos);

// Função para preencher o vetor com null
// Entrada: Vetor de chave, tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void preencher_null(int v[], int n);

// Função auxiliar para adicionar um filho com um no
// Entrada: Arvore, posicao da raiz, chave mediana, ptdados, posicao do novo no e arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo filho
void adicionaDireita(arvoreB *B, int pos, int codProd, int k, int novoFilho, int poV, FILE* f);

// Função para fazer o split da arvore B
// Entrada: Arquivo de indice, posicao do pai, chave mediana, ptDado e posicao do filho esquerdo
// Saida: Posicao do novo filho
// Pre-Condicao: No esta cheio
// Pos-Condicao: No dividido em dois
int split(FILE* f, int pos_pai, int *m, int *pt, int *posEsq);

// Função auxiliar para inserir um codigo na arvore
// Entrada: Arvore, posicao da raiz, codigo e posicao no arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo codigo
void inserirAux(FILE* arq, int pos_raiz, int codigo, int posicao);

// Função para adicionar um codigo na arvore
// Entrada: Arquivo de indice, codigo e posicao no arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo codigo
void inserirArvore(FILE* arq, int codigo, int posicao);

// Função para fazer a concatenação de dois vetores da arvore
// Entrada: Arquivo de indice, posicao do pai , posicao do filho esquerdo e direito
// Saida: Nenhuma
// Pre-Condicao: Chave sozinha em um vetor apos remocao
// Pos-Condicao: Vetores concatenados
void concatenacao(FILE* arq, int posPai, int posEsq, int posDir);

// Função para emprestar codigos do vetor da esquerda para direita
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Emprestimo realizado
void emprestimo_esq_dir(FILE* arq, int pos_pai, int pos_filho);

// Função para emprestar codigos do vetor da direita para esquerda
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Emprestimo realizado
void emprestimo_dir_esq(FILE* arq, int pos_pai, int pos_filho);

// Função para arrumar os vetores apos ocorrer underflow
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Vetor ficar com o numero minimo de chaves
// Pos-Condicao: Underflow arrumado
void underflow(FILE* arq, int posPai, int posFilho);

// Função para pegar a maior posicao
// Entrada: Arquivo de indice, posicao no arquivo, ponteiro da posicao
// Saida: Maior valor
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int maior(FILE* arq, int pos, int* prod);

// Função auxiliar para procurar uma chave na arvore
// Entrada: Vetores, posicao da esquerda, posicao da direita e o codigo
// Saida: Posicao da chave
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int procurarAux(int v[], int e, int d, int codigo);

// Função para procurar uma chave na arvore
// Entrada: Vetores, tamanho e o codigo
// Saida: Posicao da chave
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int procurarChave(int v[], int n, int codigo);

// Função auxiliar para remover uma chave na arvore
// Entrada: arquivo de indice, posicao no arquivo de dados e codigo
// Saida: Posicao no arquivo de indice
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int removerAux(FILE* arq, int pos, int x);

// Função para remover uma chave na arvore
// Entrada: Arquivo de indice e codigo
// Saida: Posicao da chave livre
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int removerArvore(FILE* arq, int codigo);

// Função auxiliar para buscar uma chave na arvore
// Entrada: Arquivo de indice, codigo e a posicao da raiz
// Saida: Posicao no arquivo
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int buscaAUX(FILE* arq, int codigo, int raiz);

// Função para buscar uma chave na arvore
// Entrada: Arquivo de indice e o codigo
// Saida: Posicao da chave no arquivo
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int buscarDados(FILE *arq, int codigo);


#endif // ARQUIVOINDICE_H
