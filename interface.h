#ifndef INTERFACE_H_INCLUDE
#define INTERFACE_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "arquivo.h"
#include "arquivoDados.h"
#include "arquivoIndice.h"

// Mostra o menu de opcoes do programa
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Nenhuma
void menu(FILE* arqDados, FILE* arqIndice);

// Mostra o menu de impressoes que podem ser feitas
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Executa a funcao escolhida
void imprimir(FILE* arqDados, FILE* arqIndice);

// Mostra o menu de remocao que podem ser feitas
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feita a remocao de um produto
void remover(FILE* arqDados, FILE* arqIndice);

// Mostra o menu de atualizaçao que podem ser feitas no produto
// Entrada: arquivo de dados e arquivo de indice
// Retorno: Nenhuma
// Pre-condicao: Nenhuma
// Pos-condicao: Feita a atualização da opção escolhida
void atualizar(FILE* arqDados, FILE* arqIndice);

#endif // INTERFACE_H_INCLUDE
