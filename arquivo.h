#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "arquivoIndice.h"
#include "arquivoDados.h"
#include "arquivo.h"

// Le a linha do arquivo e faz as remo�oes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informa��es necessarias
void lerRemocao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e faz as altera�oes nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informa��es necessarias
void lerAlteracao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e faz as inser��es nas variaveis e grava nos arquivos
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: arquivo de dados e indice preenchido com as informa��es necessarias
void lerInsercao(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le a linha do arquivo e verifica que tipo de a�ao executar
// Entrada: Arquivo lido, Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Arquivo nao esta null
// Pos-condicao: arquivo de dados e indice preenchido com as informa��es necessarias
void cleanRegister(FILE* fr, FILE* arqDados, FILE* arqIndice);

// Le o caminho do arquivo passado por input, e verifica se ele existe
// Entrada: Arquivo de Dados e Arquivo de Indice
// Retorno: Nenhuma
// Pre-condicao: Um caminho para um arquivo existente
// Pos-condicao: Arquivo lido
void loadPath(FILE* arqDados, FILE* arqIndice);


#endif // ARQUIVO_H_INCLUDED
