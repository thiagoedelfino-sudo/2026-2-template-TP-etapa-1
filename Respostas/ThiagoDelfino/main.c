#include"mapa.h"
#include<stdio.h>
#include<stdlib.h>
#include"acao_avanca.h"
#include"acao_item.h"
#include"acao_monstro.h"
#include"acao_ouro.h"
#include"acao_volta.h"
#include<string.h>

#define MAX_TAM_INDICE 21 

int main(){
    char indice[MAX_TAM_INDICE];
    Mapa *m;
    while(scanf("%s ",indice)==1){
        if(!strcmp(indice,"INICIO")){
            scanf("MAPA");
           m=criaMapa();
           continue;
        }
        if(!strcmp(indice,"OURO")){
            Ouro *o=leOuro();
            insereCelulaMapa(m,o,executaOuro,imprimeOuro,desalocaOuro);
            continue;
        }
        if(!strcmp(indice,"ITEM")){
            Item *i=leItem();
            insereCelulaMapa(m,i,executaItem,imprimeItem,desalocaItem);
            continue;
        }
        if(!strcmp(indice,"MONSTRO")){
            Monstro *m=leMonstro();
            insereCelulaMapa(m,m,executaMonstro,imprimeMonstro,desalocaMonstro);
            continue;
        }
        if(!strcmp(indice,"VAZIA")){
            insereCelulaMapa(m,NULL,NULL,NULL,NULL);
            continue;
        }
        if(!strcmp(indice,"AVANCA")){
            Avanca *a=leAvanca();
            insereCelulaMapa(m,a,executaAvanca,imprimeAvanca,desalocaAvanca);
            continue;
        }
        if(!strcmp(indice,"VOLTA")){
            Volta *v=leVolta();
            insereCelulaMapa(m,v,executaVolta,imprimeVolta,desalocaVolta);
            continue;
        }
        if(!strcmp(indice,"FIM")){
            break;
        }
    }
    
}