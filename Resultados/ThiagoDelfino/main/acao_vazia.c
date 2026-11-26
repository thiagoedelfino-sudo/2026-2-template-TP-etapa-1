#include"acao_vazia.h"
#include<stdio.h>
#include<stdlib.h>

struct Vazia{
    int nada;
};

Vazia *criaVazia(){
    Vazia *v=(Vazia*)calloc(1,sizeof(Vazia));
    return v;
}

Vazia *leVazia(){
    return criaVazia();
}

int executaVazia(void *dado,Jogador *j){
    return 0;
}

void imprimeVazia(void *dado){
    Vazia *v=(Vazia*)dado;
    printf("VAZIA");
}

void desalocaVazia(void *dado){
    Vazia *v=(Vazia*)dado;
    if(v!=NULL){
        free(v);
    }
}
