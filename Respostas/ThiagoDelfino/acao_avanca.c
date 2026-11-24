#include"acao_avanca.h"
#include<stdio.h>
#include<stdlib.h>

struct Avanca{
    int avanco;
};

Avanca *criaAvanca(int avanco){
    Avanca *a=(Avanca*)calloc(1,sizeof(Avanca));
    a->avanco;
}

Avanca *leAvanca(){
    int avanco;
    scanf("%d",&avanco);
    return criaAvanca(avanco);
}

int executaAvanca(void *dado,Jogador *j){
    Avanca *a=(Avanca*)dado;
    return a->avanco;

}

void imprimeAvanca(void *dado){
    Avanca *a=(Avanca*)dado;
    printf("AVANCA %d",a->avanco);
}

void desalocaAvanca(void dado){
    Avanca *a=(Avanca*)dado;
    if(a!=NULL)
        free(a);
}
