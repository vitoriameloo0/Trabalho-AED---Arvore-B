#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "interface.h"
#include "arquivo.h"
#include "arquivoDados.h"
#include "arquivoIndice.h"


void welcome() {
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("Trabalho 3 de Algoritmos e Estruturas de Dados\n");
    printf("      Cadastro de Produtos usando Arvore B     \n");
    printf("\n");
    printf("Alunos: Vitoria Melo e Matheus Prokopowiski\n");
    printf("Professor: Romulo Cesar Silva\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
}


FILE* inicializar_arqIndice(char* str){
    FILE* arqIndice = fopen(str, "r+b");

    if (arqIndice == NULL) {
        arqIndice = fopen(str, "w+b");
        cab_Indice *newcab = (cab_Indice*)malloc(sizeof(cab_Indice));
        newcab->topo = 0;
        newcab->raiz = -1;
        newcab->livre= -1;
        escrever_cabecalhoIndice(arqIndice, newcab);
        free(newcab);
    }
    return arqIndice;
}


FILE* inicializar_arqDados (char* str){
    FILE* arqDados = fopen(str, "r+b");
    if (arqDados == NULL) {
        arqDados = fopen(str, "w+b");
        cab_Dados *newcab = (cab_Dados*)malloc(sizeof(cab_Dados));
        newcab->pos_topo = 0;
        newcab->pos_livre = -1;
        escrever_cabecalho(arqDados, newcab);
        free(newcab);
    }
    return arqDados;
}

int main() {
    FILE* arqIndice = inicializar_arqIndice("ArquivoIndice.bin");
    FILE* arqDados = inicializar_arqDados("ArquivoDados.bin");

    welcome();
    menu(arqDados, arqIndice);

    fclose(arqDados);
    fclose(arqIndice);

    return 0;
}
