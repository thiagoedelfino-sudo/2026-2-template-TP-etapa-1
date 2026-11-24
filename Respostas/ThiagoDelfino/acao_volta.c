#include"acao_volta.h"
#include<stdio.h>
#include<stdlib.h>

struct Volta{
    int recuo;
};

Volta *criaVolta(int recuo){
    Volta *v=(Volta*)calloc(1,sizeof(Volta));
    v->recuo=recuo;
}

Volta *leVolta(){
    int recuo;
    scanf("%d",&recuo);
    return criaVolta(recuo);
}

int executaVolta(void *dado,Jogador *j){
    Volta *v=(Volta*)dado;
    return v->recuo;
}

void imprimeVolta(void *dado){
    Volta *v=(Volta*)dado;
    printf("VOLTA %d",v->recuo);
}

void desalocaVolta(void dado){
    Volta *v=(Volta*)dado;
    if(v!=NULL)
        free(v);
}
