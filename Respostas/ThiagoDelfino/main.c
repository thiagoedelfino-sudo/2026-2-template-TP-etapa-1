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
    char letra;
    int nJogadores=0;
    Jogador **jogadores;
    while(scanf("%c",&letra)==1){
        switch(letra){
            case 'J':
                jogadores=realloc(jogadores,(Jogador*)*nJogadores+1);
                jogadores[nJogadores]=leJogador();
                nJogadores++;
                break;
            default:
                break;
        }
        if(letra!='J')
            break;
    }
    int ganhou=0,numVence=0,nJogadas=0,nDisputas=0,nMonstDerr;
    while(1){
        if(letra=='F')
            break;
        if(letra=='E'){
            scanf("%s",indice);
            if(!strcmp(indice,"ESTADO")==1){
                printf("=========== ESTADO ============\n");
                printf("[INICIO]\n");
                imprimeCelulasMapa(m);
                printf("[FIM]\n");
                printf("-------------------------------\n");
                for(int i=0;i<nJogadores;i++){
                    printEstadoJogador(jogadores[i]);
                    printf("- Situacao ");
                    if(ganhou==1){
                        printf("VENCEDOR %s\n",obtemNomeJogador(jogadores[numVence]));
                    }
                    else{
                        printf("EM ANDAMENTO\n");
                    }
                }
                printf("===============================\n");
            }
            if(!strcmp(indice,"RELATORIO")==1){
                printf("========= RELATORIO ===========\n");
                printf("- Celulas do mapa: %d\n",obtemQtdCelulasMapa(m));
                printf("- Jogadores: %d\n",nJogadores);
                printf("- jogadas totais: %d\n",nJogadas);
                printf("- Disputas: %d\n",nDisputas);
                printf("- Monstros derrotados: %d\n",nMonstDerr);
                printf("- Situacaoo: Vencedor %s\n",obtemNomeJogador(jogadores[numVence]));
                printf("===============================\n");
            }
            if(!strcmp(indice,"RANKING")==1){
                for(int i=0;i<nJogadores;i++){
                    printRankingJogador(jogadores[i],i+1);
                    printf("===============================\n");
                }
            }
        }
        scanf("%c",&letra)
    }


    
}