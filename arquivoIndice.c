#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivoIndice.h"
#include "arquivoDados.h"

// Função para escrever os dados do cabeçalho no arquivo
// Entrada: Arquivo binario e ponteiro do dados do cabeçalho pra gravar
// Retorno: Nenhuma
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Escrita do dado no arquivo binario
void escrever_cabecalhoIndice(FILE* f, cab_Indice* cab){
    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(cab_Indice), 1, f);
}

// Funcao para le o cabeçalho do arquivo binario
// Entrada: Arquivo Binario
// Retorno: Ponteiro do cabeçalho
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: Cabeçalho do arquivo retornado
cab_Indice* le_cabecalhoIndice(FILE* f){
    cab_Indice* cab = (cab_Indice*) malloc(sizeof(cab_Indice));
    fseek(f, 0, SEEK_SET);
    fread(cab, sizeof(cab_Indice), 1, f);
    return cab;
}

// Função para le os dados do produto em uma determinada posicao do arquivo
// Entrada: Arquivo binario e posicao do produto
// Retorno: Ponteiro do Produto
// Pre-Condicao: Arquivo binario criado
// Pos-Condicao: No do produto retornado
arvoreB* le_noArvore(FILE* f, int pos){
    arvoreB* aux = (arvoreB*) malloc (sizeof(arvoreB));
    fseek(f, sizeof(cab_Indice) + sizeof(arvoreB)*pos, SEEK_SET);
    fread(aux, sizeof(arvoreB), 1, f);
    return aux;
}

// Funcao para escrever no arquivo binario os codigo do produto e suas informaçoes
// Entrada: Arquivo Binario, o produto e a posicao
// Retorno: Nenhum
// Pre-Condicao: Arquivo binario criado e os dados do produto
// Pos-Condicao: Dados escrito no arquivo binario
void escreve_noArvore(FILE* arq, arvoreB* x, int posicao){
    fseek(arq, sizeof(cab_Indice)+ posicao*sizeof(arvoreB), SEEK_SET);
    fwrite(x, sizeof(arvoreB), 1, arq);
}

// Função para inserir os codigos dos produto no arquivo binario em uma determinada posicao
// Entrada: Arquivo binario com as informações, arvore com os dados e a posiçao do dado no arquivo de dado
// Retorno: Posicao em que os dados foram inserido no arquivo de indice
// Pre-Condicao: Ter inserido os dados no arquivo de dados
// Pos-Condicao: Codigo e suas informações inserido no arquivo
int insercaoArqIndice(FILE* f, arvoreB* arv, int pos){
    int pos_escrita;
    if(pos==-1){ // Escrever na próxima posição disponível
        cab_Indice* cab = le_cabecalhoIndice(f);
        if(cab->livre==-1){ // Escrever no topo
            fseek(f, sizeof(cab_Indice) + sizeof(arvoreB)*cab->topo, SEEK_SET);
            fwrite(arv, sizeof(arvoreB), 1, f);

            pos_escrita = cab->topo;

            cab->topo++;
        }

        else{ // Escrever na posição livre
            int pos_aux;

            arvoreB* aux = le_no(f, cab->livre); // Ler cabeça dos livres
            pos_aux = cab->livre;
            cab->livre = aux->filhos[0];

            fseek(f, sizeof(cab_Indice) + sizeof(arvoreB)*pos_aux, SEEK_SET);
            fwrite(arv, sizeof(arvoreB), 1, f);

            pos_escrita = pos_aux;

            free(aux);
        }
        escrever_cabecalhoIndice(f, cab);
        free(cab);
    }
    else{ // Escrever na posição escolhida
        fseek(f, sizeof(cab_Indice) + sizeof(arvoreB)*pos, SEEK_SET);
        fwrite(arv, sizeof(arvoreB), 1, f);
        pos_escrita = pos;
    }
    return pos_escrita;
}

// Função auxiliar para imprimir as posições livres de forma recursiva do arquivo de indice
// Entrada: arquivo de indice, primeira posicao livre
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivresIndiceAUX(FILE* arq, int posicao){
    if(posicao == -1) return;

    printf("%d ", posicao);
    int prox;
    arvoreB* arvore = le_noArvore(arq, posicao);
    prox = arvore->filhos[0];
    free(arvore);
    imprimirLivresIndiceAUX(arq, prox);
}

// Função para imprimir as posições livres arquivo de indice
// Entrada: arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLivresIndice(FILE* arq){
    cab_Indice* cab = le_cabecalhoIndice(arq);
    int posLivre = cab->livre;
    free(cab);
    printf("Livres Indice: ");
    imprimirLivresIndiceAUX(arq, posLivre);
    printf("\n");
}

// Função para fazer a copia dos dados do vetor v1 para v
// Entrada: Vetores v e v1, e o tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados copiados
void copiarVetor(int v[], int v1[], int n){
    for(int i = 0; i < n; i++){
         v[i] = v1[i];
    }
}

// Função para imprimir os dados de um vetor
// Entrada: Vetores v e o tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados imprimido
void imprimirVetor(int v[], int n){
    printf("[");
    for(int i = 0; i < n-1; i++) printf("%d,", v[i]);
    printf("%d]", v[n-1]);
}

// Função para imprimir a lista de dados que estão em um vetor
// Entrada: Arquivo de indice, posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirLista(lista* lista, int andar){
    if(lista == NULL)
        return;
    if(lista->andar > andar){
        printf("\n\n");
        imprimirVetor(lista->v, lista->n);
        printf(" ");
        imprimirLista(lista->prox, lista->andar);
    }
    else{
        imprimirVetor(lista->v, lista->n);
        printf(" ");
        imprimirLista(lista->prox, lista->andar);
    }
}

// Função para inserir os dados na lista do arquivo de indice, encadeando as informaçoes inseridas
// Entrada: Lista, andar, vetor e o tamanho
// Saida: Lista
// Pre-Condicao: Nenhuma
// Pos-Condicao: Dados copiados
lista* inserirLista(lista* l, int andar, int v[], int n){
    if(l == NULL || andar < l->andar){
        lista* aux = (lista*) malloc (sizeof(lista));
        aux->andar = andar;
        copiarVetor(aux->v, v, n);
        aux->n = n;
        aux->prox = l;
        return aux;
    }
    l->prox = inserirLista(l->prox, andar, v, n);
    return l;
}

// Função para percorrer a arvore pelo arquivo de indice
// Entrada: Arquivo de indice, posicao da raiz, inicio da lista e o andar inicial
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Arvore percorrida
void percorrerArvore(FILE* arq, int pos, lista** l, int andar){
    if(pos == -1) return;
    arvoreB* arvore = le_noArvore(arq, pos);
    *l = inserirLista(*l, andar, arvore->chaves, arvore->numChaves);
    for(int i = 0; i < arvore->numChaves+1; i++){
        percorrerArvore(arq, arvore->filhos[i], l, andar+1);
    }
    free(arvore);
}

// Função para imprimir os valores que estao na arvore em cada andar
// Entrada: Arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirArvore(FILE* arq){
    cab_Indice* cab = le_cabecalhoIndice(arq);
    if(cab->raiz == -1)
        return;
    lista* l = NULL;
    percorrerArvore(arq, cab->raiz, &l, 0);
    imprimirLista(l, 0);
    printf("\n");
    free(cab);
}

// Função auxiliar para imprimir os codigos em ordem crescente
// Entrada: Arquivo de indice e posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void imprimirInOrdemAUX(FILE* arq, int pos){
    if(pos == -1) return;
    arvoreB* arvore = le_noArvore(arq, pos);
    for(int i = 0; i< arvore->numChaves; i++){
        imprimirInOrdemAUX(arq, arvore->filhos[i]);
        printf("%d ", arvore->chaves[i]);
    }
    imprimirInOrdemAUX(arq, arvore->filhos[arvore->numChaves]);
    free(arvore);
}

// Função para imprimir a lista de dados em ordem crescente
// Entrada: Arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Valores impresso
void imprimirInOrdem(FILE* arq){
    printf("Codigos InOrdem: ");
    cab_Indice* cab = le_cabecalhoIndice(arq);
    imprimirInOrdemAUX(arq, cab->raiz);
    free(cab);
    printf("\n");
}

// Função para preencher o vetor com null
// Entrada: Vetor de chave, tamanho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void preencher_null(int v[], int n){
    for(int i=0 ; i<n ; v[i++]=-1);
}

// Função para empurrar os dados de um vetor para abrir um espaço
// Entrada: Vetor de chave, tamanho e o posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void empurrar(int v[], int n, int pos){
    for(int i = n-1; i > pos; i--){
        v[i] = v[i-1];
    }
}

// Função para inserir a posicao do produto no arquivo de dados no arquivo de indice
// Entrada: Vetor de PtDados, posicao no arqIndice, posicao do arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: PtDado inserida e devolução de sua posicao no arquivo
void inserirPT(int v[], int n, int posicao, int pos){
    empurrar(v, n, pos);
    v[pos]= posicao;
    return pos;
}

// Função para inserir as chaves
// Entrada: Vetor de chave, tamanho e o codigo
// Saida: Posicao que a chav
// Pre-Condicao: Nenhuma
// Pos-Condicao: Chave inserida e devolução de sua posicao no arquivo
int inserirChave(int v[], int n, int codigo){
    int pos = procurarChave(v, n-1, codigo);
    empurrar(v, n, pos);
    v[pos] = codigo;
    return pos;
}

// Função auxiliar para adicionar um filho com um no
// Entrada: Arvore, posicao da raiz, chave mediana, ptdados, posicao do novo no e arquivo de indice
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo filho
void adicionaDireita(arvoreB *B, int pos, int codProd, int k, int novoFilho, int poV, FILE* f){
    int i;
    for(i = B->numChaves; i > pos; i--){
        B->chaves[i] = B->chaves[i-1];
        B->filhos[i+1] = B->filhos[i];
        B->ptDados[i] = B->ptDados[i-1];
    }
    B->chaves[pos] = codProd;
    B->ptDados[pos] = k;
    B->filhos[pos+1] = novoFilho;
    B->numChaves++;
    insercaoArqIndice(f, B, poV);

}

// Função para fazer o split da arvore B
// Entrada: Arquivo de indice, posicao do pai, chave mediana, ptDado e posicao do filho esquerdo
// Saida: Posicao do novo filho
// Pre-Condicao: No esta cheio
// Pos-Condicao: No dividido em dois
int split(FILE* f, int pos_pai, int *m, int *pt, int *posEsq){
    int pos_aux;
    arvoreB* esq, *dir;

    esq = le_noArvore(f, pos_pai);
    dir = (arvoreB*) malloc(sizeof(arvoreB));
    dir->numChaves = 0;

    preencher_null(dir->filhos, ORDEM+1);

    int min = ORDEM/2;

    // Adiciona chave média da esquerda em pai
    *m = esq->chaves[min];
    *pt = esq->ptDados[min];

    // Adiciona metade direita das chaves da esquerda em direita
    for(int i=min+1 ; i<esq->numChaves ; i++){
        dir->filhos[dir->numChaves] = esq->filhos[i];
        esq->filhos[i] = -1;

        dir->numChaves++;
        pos_aux = inserirChave(dir->chaves, dir->numChaves, esq->chaves[i]);
                    inserirPT(dir->ptDados, dir->numChaves, esq->ptDados[i], pos_aux);
    }
    dir->filhos[dir->numChaves] = esq->filhos[esq->numChaves];
    esq->filhos[esq->numChaves] = -1;
    esq->numChaves = min;

    *posEsq = insercaoArqIndice(f, esq,pos_pai);

    int posDir = insercaoArqIndice(f, dir, -1);
    free(dir);
    free(esq);

    return posDir;
}

// Função auxiliar para inserir um codigo na arvore
// Entrada: Arvore, posicao da raiz, codigo e posicao no arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo codigo
void inserirAux(FILE* f, int pos, int x, int prod){
    arvoreB* arv = le_noArvore(f, pos);
    int pos_x = procurarChave(arv->chaves, arv->numChaves, x);
    if(x == arv->chaves[ pos_x ]){ // X já existe no nó
        free(arv);
        return;
    }

    if(arv->filhos[0]==-1){ // Está em uma folha, inserir a chave
        arv->numChaves++;
        int pos_chave = inserirChave(arv->chaves, arv->numChaves, x);
        inserirPT(arv->ptDados, arv->numChaves, prod, pos_chave);
        insercaoArqIndice(f, arv, pos);
        free(arv);
        return;
    }

    else{ // Está em nó interno, inserir em filho e verificar se houve overflow
        int pos_filho = arv->filhos[pos_x];
        free(arv);
        inserirAux(f, pos_filho, x, prod);
        arvoreB* filho = le_noArvore(f, pos_filho);

        if(filho->numChaves==ORDEM){ // Deu overflow
            free(filho);
            int chaveM, ptDado, posEsq;
            int posNo = split(f, pos_filho, &chaveM, &ptDado, &posEsq);

            arv = le_noArvore(f, pos);
            adicionaDireita(arv, pos_x, chaveM, ptDado, posNo, pos, f);
            /*pos_x = adicionar_v(arv->chaves, arv->n, chaveM);
            inserir_v(arv->ptDados, arv->n, ptDado, pos_x);

            for(int i= arv->n; i>pos_x;i--)
                arv->filhos[i+1]=arv->filhos[i];

            arv->filhos[pos_x+1] = posNo;
            arv->n++;
            */

            //
            //write_no_b(f, arv, pos);
        }
    }

}

// Função para adicionar um codigo na arvore
// Entrada: Arquivo de indice, codigo e posicao no arquivo de dados
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Adicionado o novo codigo
void inserirArvore(FILE* f, int x, int prod){
    cab_Indice* cab = le_cabecalhoIndice(f);
    int pos_raiz = cab->raiz;
    free(cab);

    if(pos_raiz==-1){ // Árvore vazia
        int nova_raiz;
        arvoreB* arv = (arvoreB*) malloc(sizeof(arvoreB));
        inserirChave(arv->chaves, 1, x);
        inserirPT(arv->ptDados, 1, prod, 0);
        preencher_null(arv->filhos, ORDEM+1);
        arv->numChaves = 1;

        nova_raiz = insercaoArqIndice(f, arv, -1);
        cab = le_cabecalhoIndice(f);
        cab->raiz = nova_raiz;
        escrever_cabecalhoIndice(f, cab);
        free(cab);
        free(arv);
    }

    else{
        inserirAux(f, pos_raiz, x, prod);
        // Verificar overflow na raiz (caso de split normal)
        arvoreB* raiz = le_noArvore(f, pos_raiz);

        if(raiz->numChaves==ORDEM){
            int chaveM, ptDado, posEsq;

           int posD = split(f, pos_raiz, &chaveM, &ptDado, &posEsq);

            arvoreB *novaraiz = (arvoreB*) malloc(sizeof(arvoreB));
            novaraiz->chaves[0] = chaveM;
            novaraiz->ptDados[0] = ptDado;
            novaraiz->filhos[0] = posEsq;
            novaraiz->filhos[1] = posD;
            novaraiz->numChaves=1;
            for(int i = 2; i < ORDEM; i++)
                    novaraiz->filhos[i] = NULL; //-1


            int pNova = insercaoArqIndice(f, novaraiz, -1);

            cab = le_cabecalhoIndice(f);
            cab->raiz = pNova;
            escrever_cabecalhoIndice(f, cab);
            free(cab);
            free(novaraiz);
        }
    }

}

// Função para fazer a concatenação de dois vetores da arvore
// Entrada: Arquivo de indice, posicao do pai , posicao do filho esquerdo e direito
// Saida: Nenhuma
// Pre-Condicao: Chave sozinha em um vetor apos remocao
// Pos-Condicao: Vetores concatenados
void concatenacao(FILE* arq, int posPai, int posEsq, int posDir){
    int pos_aux;
    arvoreB* pai, *esq, *dir, *meio;

    pai = le_noArvore(arq, posPai);
    esq = le_noArvore(arq, pai->filhos[posEsq]);
    dir = le_noArvore(arq, pai->filhos[posDir]);

    // 1: Junta em esq a chave separadora do pai
    esq->numChaves++;
    pos_aux = inserirChave(esq->chaves, esq->numChaves, pai->chaves[posEsq]);
    inserirPT(esq->ptDados, esq->numChaves, pai->ptDados[posEsq], pos_aux);
    puxar(pai->chaves, pai->numChaves, posEsq);
    puxar(pai->ptDados, pai->numChaves, posEsq);

    // 2: Passa todas as chaves e filhos de dir para esq
    for(int i=0 ; i<dir->numChaves ; i++){
        esq->filhos[esq->numChaves] = dir->filhos[i];
        esq->numChaves++;
        pos_aux = inserirChave(esq->chaves, esq->numChaves, dir->chaves[i]);
        inserirPT(esq->ptDados, esq->numChaves, dir->ptDados[i], pos_aux);
    }
    esq->filhos[esq->numChaves] = dir->filhos[dir->numChaves];

    // 3: Adiciona nó dir na lista de livres
    cab_Indice* cab = le_cabecalhoIndice(arq);
    dir->filhos[0] = cab->livre;
    cab->livre = pai->filhos[posDir];

    // 4: Remove o nó dir do pai
    puxar(pai->filhos, pai->numChaves+1, posDir);
    pai->filhos[pai->numChaves] = -1;
    pai->numChaves--;

    insercaoArqIndice(arq, pai, posPai);
    insercaoArqIndice(arq, esq, pai->filhos[posEsq]);
    insercaoArqIndice(arq, dir, cab->livre);
    escrever_cabecalhoIndice(arq, cab);

    free(pai);
    free(esq);
    free(dir);
    free(cab);
}

// Função para emprestar codigos do vetor da esquerda para direita
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Emprestimo realizado
void emprestimo_esq_dir(FILE* arq, int pos_pai, int pos_filho){
    int pos_aux;
    arvoreB* filho, *pai, *irmao_dir;

    pai = le_noArvore(arq, pos_pai);
    filho = le_noArvore(arq, pai->filhos[pos_filho]);
    irmao_dir = le_noArvore(arq, pai->filhos[pos_filho+1]);

    // Insere em irmão a chave separadora do pai
    irmao_dir->numChaves++;
    pos_aux = inserirChave(irmao_dir->chaves, irmao_dir->numChaves, pai->chaves[pos_filho]);
    inserirPT(irmao_dir->ptDados, irmao_dir->numChaves, pai->ptDados[pos_filho], pos_aux);
    // Insere em irmão o filho mais à direita do filho
    empurrar(irmao_dir->filhos, irmao_dir->numChaves+1, 0);
    irmao_dir->filhos[0] = filho->filhos[filho->numChaves];
    // Pai substitui chave separadora pela chave mais à direita do filho
    pai->chaves[pos_filho] = filho->chaves[filho->numChaves-1];
    pai->ptDados[pos_filho] = filho->ptDados[filho->numChaves-1];
    // Filho tem filho mais à direita nulo
    filho->filhos[filho->numChaves] = -1;
    filho->numChaves--;

    insercaoArqIndice(arq, pai, pos_pai);
    insercaoArqIndice(arq, filho, pai->filhos[pos_filho]);
    insercaoArqIndice(arq, irmao_dir, pai->filhos[pos_filho+1]);

    free(pai);
    free(filho);
    free(irmao_dir);
}

// Função para emprestar codigos do vetor da direita para esquerda
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Emprestimo realizado
void emprestimo_dir_esq(FILE* arq, int pos_pai, int pos_filho){
    int pos_aux;
    arvoreB* filho, *pai, *irmao_esq;

    pai = le_noArvore(arq, pos_pai);
    filho = le_noArvore(arq, pai->filhos[pos_filho]);
    irmao_esq = le_noArvore(arq, pai->filhos[pos_filho-1]);

    // Insere em irmão a chave separadora do pai
    irmao_esq->numChaves++;
    pos_aux =  inserirChave(irmao_esq->chaves, irmao_esq->numChaves, pai->chaves[pos_filho-1]);
    inserirPT(irmao_esq->ptDados, irmao_esq->numChaves, pai->ptDados[pos_filho-1], pos_aux);

    // Insere em irmão o filho mais à esquerda do filho
    irmao_esq->filhos[irmao_esq->numChaves]  = filho->filhos[0];

    // Pai substitui chave separadora pela chave mais à esquerda do filho
    pai->chaves[pos_filho-1] = filho->chaves[0];
    pai->ptDados[pos_filho-1] = filho->ptDados[0];

    // Filho tem chave mais à esquerda desconsiderada
    puxar(filho->chaves, filho->numChaves, 0);
    puxar(filho->ptDados, filho->numChaves, 0);

    // Filho tem filho direita à esquerda desconsiderado
    puxar(filho->filhos, filho->numChaves+1, 0);
    filho->filhos[filho->numChaves] = -1;
    filho->numChaves--;

    insercaoArqIndice(arq, pai, pos_pai);
    insercaoArqIndice(arq, filho, pai->filhos[pos_filho]);
    insercaoArqIndice(arq, irmao_esq, pai->filhos[pos_filho-1]);

    free(pai);
    free(filho);
    free(irmao_esq);
}

// Função para arrumar os vetores apos ocorrer underflow
// Entrada: Arquivo de indice, posicao do pai e posicao do filho
// Saida: Nenhuma
// Pre-Condicao: Vetor ficar com o numero minimo de chaves
// Pos-Condicao: Underflow arrumado
void underflow(FILE* arq, int posPai, int posFilho){
    arvoreB* filho, *pai, *irmaoEsq=NULL, *irmaoDir=NULL;

    pai = le_noArvore(arq, posPai);
    filho = le_noArvore(arq, pai->filhos[posFilho]);

    int min = (ORDEM-1)/2;

    // 1: checar irmãos
    if(posFilho != 0){ // Tem irmão à esquerda
        irmaoEsq = le_noArvore(arq, pai->filhos[posFilho-1]);
    }
    if(posFilho != ORDEM-2 && pai->filhos[posFilho+1] != -1){ // Tem irmão à direita
        irmaoDir = le_noArvore(arq, pai->filhos[posFilho+1]);
    }

    // 2: verificar se é possível fazer empréstimo
    if(irmaoEsq!=NULL && irmaoEsq->numChaves > min){ // Empréstimo do irmão da esquerda ao filho
        free(pai);
        free(filho);
        if(irmaoEsq!=NULL) free(irmaoEsq);
        if(irmaoDir!=NULL) free(irmaoDir);
        emprestimo_esq_dir(arq, posPai, posFilho-1);
    }
    else if(irmaoDir != NULL && irmaoDir->numChaves > min){ // Empréstimo do irmão da direita ao filho
        free(pai);
        free(filho);
        if(irmaoEsq!=NULL) free(irmaoEsq);
        if(irmaoDir!=NULL) free(irmaoDir);
        emprestimo_dir_esq(arq, posPai, posFilho+1);
    }

    // 3: fazer concatenação
    else{
        if(irmaoEsq!=NULL){
            free(pai);
            free(filho);
            if(irmaoEsq!=NULL) free(irmaoEsq);
            if(irmaoDir!=NULL) free(irmaoDir);
            concatenacao(arq, posPai, posFilho-1, posFilho);
        }
        else if(irmaoDir!=NULL){
            free(pai);
            free(filho);
            if(irmaoEsq!=NULL) free(irmaoEsq);
            if(irmaoDir!=NULL) free(irmaoDir);
            concatenacao(arq, posPai, posFilho, posFilho+1);
        }
    }

}

// Função para pegar a maior posicao
// Entrada: Arquivo de indice, posicao no arquivo, ponteiro da posicao
// Saida: Maior valor
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int maior(FILE* arq, int pos, int* prod){
    arvoreB* arvore = le_noArvore(arq, pos);

    int maior_filho = arvore->filhos[arvore->numChaves];
    int maior_chave = arvore->chaves[arvore->numChaves-1];
    int maior_prod = arvore->ptDados[arvore->numChaves-1];
    free(arvore);

    if(maior_filho==-1){
        *prod = maior_prod;
        return maior_chave;
    }

    return maior(arq, maior_filho, prod);
}

// Função para puxar os dados de um vetor para fechar um espaço
// Entrada: Vetor de chave, tamanho e o posicao
// Saida: Nenhuma
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
void puxar(int v[], int n, int pos){
    for(int i = pos; i < n-1; i++){
         v[i] = v[i+1];
    }
}

// Função auxiliar para procurar uma chave na arvore
// Entrada: Vetores, posicao da esquerda, posicao da direita e o codigo
// Saida: Posicao da chave
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int procurarAux(int v[], int e, int d, int codigo){
    int meio = (e+d)/2;
    if(d <= e) return meio;
    if(v[meio] == codigo) return meio;
    if(v[meio] > codigo) return procurarAux(v, e, meio-1, codigo);
    return procurarAux (v, meio+1, d, codigo);
}

// Função para procurar uma chave na arvore
// Entrada: Vetores, tamanho e o codigo
// Saida: Posicao da chave
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int procurarChave(int v[], int n, int codigo){
    int pos = procurarAux(v, 0, n-1, codigo);
    if(pos < n && codigo > v[pos]) pos++;
    return pos;
}

// Função auxiliar para remover uma chave na arvore
// Entrada: arquivo de indice, posicao no arquivo de dados e codigo
// Saida: Posicao no arquivo de indice
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int removerAux(FILE* f, int pos, int x){
    int prod=-1;
    arvoreB* arv = le_noArvore(f, pos);

    int pos_x = procurarChave(arv->chaves, arv->numChaves, x);

    if(x == arv->chaves[pos_x]){ // X está nesse nó na posição pos_x
        prod = arv->ptDados[pos_x];
        if(arv->filhos[0]==-1){ // Está em uma folha, remover a chave
            puxar(arv->chaves, arv->numChaves, pos_x);
            puxar(arv->ptDados, arv->numChaves, pos_x);
            puxar(arv->filhos, arv->numChaves+1, pos_x);
            arv->numChaves--;
            insercaoArqIndice(f, arv, pos);
            free(arv);
            return prod;
        }

        else{ // X está em um nó interno, substituir pela maior chave da esquerda
            int pos_filho = arv->filhos[pos_x];
            int maior_prod;
            int maior_filho = maior(f, pos_filho, &maior_prod);
            arv->chaves[pos_x] = maior_filho;
            arv->ptDados[pos_x] = maior_prod;
            insercaoArqIndice(f, arv, pos);
            free(arv);
            removerAux(f, pos_filho, maior_filho);

            // Verificar se deu underflow
            arv = le_noArvore(f, pos_filho);
            if(arv->numChaves < (ORDEM-1)/2){
                free(arv);
                underflow(f, pos, pos_x);
                return prod;
            }
            free(arv);
            return prod;
        }
    }

    else{ // Está em nó mais abaixo
        int pos_filho = arv->filhos[pos_x];
        free(arv);
        if(pos_filho!=-1){
            prod = removerAux(f, pos_filho, x);
            arvoreB* filho = le_noArvore(f, pos_filho);

            if(filho->numChaves < (ORDEM-1)/2){ // Deu underflow
                free(filho);
                underflow(f, pos, pos_x);
                return prod;
            }
            free(filho);
            return prod;
        }
        return prod;
    }
}

// Função para remover uma chave na arvore
// Entrada: Arquivo de indice e codigo
// Saida: Posicao da chave livre
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int removerArvore(FILE* f, int x){
    cab_Indice* cab = le_cabecalhoIndice(f);
    int pos_raiz = cab->raiz;
    int prod = -1;
    free(cab);

    if(pos_raiz!=-1){ // Árvore não está vazia

        prod = removerAux(f, pos_raiz, x);

        // Verificar underflow na raiz (substituir raiz)
        arvoreB* raiz = le_noArvore(f, pos_raiz);
        if(raiz->numChaves==0){ // Deu underflow
            cab = le_cabecalhoIndice(f);

            // Troca raiz da árvore
            cab->raiz = raiz->filhos[0];

            // Adiciona raiz antiga na lista de livres
            raiz->filhos[0] = cab->livre;
            cab->livre = pos_raiz;
            insercaoArqIndice(f, raiz, pos_raiz);
            escrever_cabecalhoIndice(f, cab);
            free(cab);
        }
        free(raiz);
    }

    return prod;
}

// Função auxiliar para buscar uma chave na arvore
// Entrada: Arquivo de indice, codigo e a posicao da raiz
// Saida: Posicao no arquivo
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int buscaAUX(FILE* arq, int codigo, int posRaiz){
    arvoreB* arvore = le_noArvore(arq, posRaiz);
    int posCodigo = procurarChave(arvore->chaves, arvore->numChaves, codigo);
    int prod = -1;

    if(codigo == arvore->chaves[posCodigo]){
        prod = arvore->ptDados[posCodigo];
        free(arvore);
        return prod;
    }

    else{
        int posFilho = arvore->filhos[posCodigo];
        free(arvore);
        if(posFilho != 1){
            prod = buscaAUX(arq, codigo, posFilho);
            return prod;
        }
    }
    return prod;
}

// Função para buscar uma chave na arvore
// Entrada: Arquivo de indice e o codigo
// Saida: Posicao da chave no arquivo
// Pre-Condicao: Nenhuma
// Pos-Condicao: Nenhuma
int buscarDados(FILE *arq, int codigo){
    cab_Indice* cab = le_cabecalhoIndice(arq);
    int posRaiz = cab->raiz;
    free(cab);
    if(posRaiz != -1)
        return buscaAUX(arq, codigo, posRaiz);
    return -1;
}




