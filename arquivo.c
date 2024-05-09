#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "arquivoDados.h"
#include "arquivoIndice.h"

// Le a linha do arquivo e faz as remoçoes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerRemocao(FILE* txt, FILE* arqDados, FILE* arqIndice){
    char str[MAX];
    int codigo;

    fscanf(txt, "%[^\n]%*c", str);
    codigo = atoi(str);

    int pos = removerArvore(arqIndice, codigo);
    if(pos!=-1){
        removerDados(arqDados, pos);
    }
}

// Le a linha do arquivo e faz as alteraçoes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerAlteracao(FILE* txt, FILE* arqDados, FILE* arqIndice){
    char str[100]="";
    int codigo, estoque, real, centavo;
    Produto* p;

    fscanf(txt, "%[^;];", str);
    codigo = atoi(str);

    int pos = buscarDados(arqIndice, codigo);
    if(pos!=-1){
        p = le_no(arqDados, pos);
    }

    strcpy(str, "");
    fscanf(txt, "%[^;];", str);
    if(strpbrk(str, "1234567890")!=NULL){
        estoque = atoi(str);
        if(pos!=-1){
            p->estoque = estoque;
            insercaoArqDados(arqDados, p, pos);
        }
    }
    else fscanf(txt, ";");

    strcpy(str, "");
    fscanf(txt, "%[^\n]%*c", str);
    if(strpbrk(str, "1234567890")!=NULL){
        real = atoi(str);
        centavo = (strpbrk(str, ",.")==NULL) ? 0 : atoi(strpbrk(str, ",.")+1);
        if(pos!=-1){
            p->valorProduto = real+centavo/100.0;
            insercaoArqDados(arqDados, p, pos);
        }
    }

    if(pos!=-1){
        free(p);
    }
}

// Le a linha do arquivo e faz as inserções nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerInsercao(FILE* txt, FILE* arqDados, FILE* arqIndice){
    char str[MAX], nome[MAXX], marca[MAXY], categoria[MAXX];
    int codigo, estoque, real, centavos;

    fscanf(txt, "%[^;];", str);
    codigo = atoi(str);

    fscanf(txt, "%[^;];", nome);

    fscanf(txt, "%[^;];", marca);

    fscanf(txt, "%[^;];", categoria);

    fscanf(txt, "%[^;];", str);
    estoque = atoi(str);

    fscanf(txt, "%[^\n]%*c", str);
    real = atoi(str);
    centavos = (strpbrk(str, ",.")==NULL) ? 0 : atoi(strpbrk(str, ",.")+1);

    Produto* p = (Produto*) malloc(sizeof(Produto));
    p->codigo = codigo;
    strcpy(p->nomeProduto, nome);
    strcpy(p->marca, marca);
    strcpy(p->categoriaProduto, categoria);
    p->estoque = estoque;
    p->valorProduto = real+centavos/100.0;

    int pos = insercaoArqDados(arqDados, p, -1);
    inserirArvore(arqIndice, codigo, pos);
    free(p);
}

// Le a linha do arquivo e verifica que tipo de açao executar
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Arquivo nao esta null
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void cleanRegister(FILE* txt, FILE* arqDados, FILE* arqIndice) {
    char str[MAX], oper[] = "IAR";
    char c;
    while(fscanf(txt, "%[^;];", str)!=EOF){
        c = (strpbrk(str, oper)==NULL) ? 'x' : strpbrk(str, oper)[0];
        switch (c){
        case 'I':
            lerInsercao(txt, arqDados, arqIndice);
            break;
        case 'A':
            lerAlteracao(txt, arqDados, arqIndice);
            break;
        case 'R':
            lerRemocao(txt, arqDados, arqIndice);
            break;
        default:
            fscanf(txt, "%[^\n]%*c");
        }

    }
}

// Le o caminho do arquivo passado por input, e verifica se ele existe
// Entrada: Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Um caminho para um arquivo existente
// Pos-condicao: Arquivo lido
void loadPath(FILE *arqDados, FILE *arqIndice) {
    char str[MAX];
    FILE* txt;
    printf("Nome do Arquivo: ");
    scanf("%[^\n]%*c", str);
    txt = fopen(str, "r");
    if(txt==NULL){
        printf("Arquivo Invalido!\n");
    }
    else{
        cleanRegister(txt, arqDados, arqIndice);
        printf("Arquivo Lido!\n");
        fclose(txt);
    }
}



