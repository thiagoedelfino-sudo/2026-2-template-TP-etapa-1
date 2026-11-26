#include"acao_ouro.h"
#include<stdio.h>
#include<stdlib.h>

struct Ouro{
    int moedas;
};

Ouro *criaOuro(int moedas){
    Ouro *o=(Ouro*)calloc(1,sizeof(Ouro));
    o->moedas=moedas;
    return o;
}

Ouro *leOuro(){
    int moedas;
    scanf("%d",&moedas);
    return criaOuro(moedas);
}

int executaOuro(void *dado,Jogador *j){
    Ouro *o=(Ouro*)dado;
    adicionaOuroJogador(j,o->moedas);
    return 0;
}

void imprimeOuro(void *dado){
    Ouro *o=(Ouro*)dado;
    printf("OURO %d",o->moedas);
}

void desalocaOuro(void *dado){
    Ouro *o=(Ouro*)dado;
    if(o!=NULL)
        free(o);
}