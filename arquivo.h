#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "arquivoIndice.h"
#include "arquivoDados.h"
#include "arquivo.h"

// Le a linha do arquivo e faz as remoçoes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerRemocao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e faz as alteraçoes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerAlteracao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e faz as inserções nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void lerInsercao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e verifica que tipo de açao executar
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Arquivo nao esta null
// Pos-condicao: arquivo de dados e indice preenchido com as informações necessarias
void cleanRegister(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le o caminho do arquivo passado por input, e verifica se ele existe
// Entrada: Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Um caminho para um arquivo existente
// Pos-condicao: Arquivo lido
void loadPath(FILE* arqDados, FILE* arqIndice);


#endif // ARQUIVO_H_INCLUDED
