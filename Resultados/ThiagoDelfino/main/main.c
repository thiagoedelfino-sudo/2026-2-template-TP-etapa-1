#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "acao_monstro.h"
#include "dado.h"

#define MAX_TAM_INDICE 21

/* ===================== Acoes (movidas para o main) ===================== */

#define MAX_TAM_NOME_ITEM 21

/* ---- OURO ---- */
typedef struct Ouro {
    int moedas;
} Ouro;

static Ouro *criaOuro(int moedas){
    Ouro *o=(Ouro*)calloc(1,sizeof(Ouro));
    o->moedas=moedas;
    return o;
}

static Ouro *leOuro(){
    int moedas;
    scanf("%d",&moedas);
    return criaOuro(moedas);
}

static int executaOuro(void *dado,Jogador *j){
    Ouro *o=(Ouro*)dado;
    adicionaOuroJogador(j,o->moedas);
    return 0;
}

static void imprimeOuro(void *dado){
    Ouro *o=(Ouro*)dado;
    printf("OURO %d",o->moedas);
}

static void desalocaOuro(void *dado){
    Ouro *o=(Ouro*)dado;
    if(o!=NULL)
        free(o);
}

/* ---- ITEM ---- */
typedef struct Item {
    char nome[MAX_TAM_NOME_ITEM];
    int preco,bonus;
} Item;

static Item *criaItem(char *nome,int preco, int bonus){
    Item *i=(Item*)calloc(1,sizeof(Item));
    strcpy(i->nome,nome);
    i->preco=preco;
    i->bonus=bonus;
    return i;
}

static Item *leItem(){
    char nome[MAX_TAM_NOME_ITEM];
    int preco,bonus;
    scanf("%s %d %d",nome,&preco,&bonus);
    return criaItem(nome,preco,bonus);
}

static int executaItem(void *dado, Jogador *j) {
    Item *i = (Item *)dado;
    if (obtemOuroJogador(j) >= i->preco) {
        adicionaOuroJogador(j, -i->preco);
        adicionaForcaJogador(j, i->bonus);
    }
    return 0;
}

static void imprimeItem(void *dado){
    Item *i=(Item*)dado;
    printf("ITEM %s (P:%d F:+%d)",i->nome,i->preco,i->bonus);
}

static void desalocaItem(void *dado){
    Item *i=(Item*)dado;
    if(i!=NULL)
        free(i);
}

/* ---- AVANCA ---- */
typedef struct Avanca {
    int avanco;
} Avanca;

static Avanca *criaAvanca(int avanco){
    Avanca *a=(Avanca*)calloc(1,sizeof(Avanca));
    a->avanco=avanco;
    return a;
}

static Avanca *leAvanca(){
    int avanco;
    scanf("%d",&avanco);
    return criaAvanca(avanco);
}

static int executaAvanca(void *dado,Jogador *j){
    Avanca *a=(Avanca*)dado;
    return a->avanco;

}

static void imprimeAvanca(void *dado){
    Avanca *a=(Avanca*)dado;
    printf("AVANCA %d",a->avanco);
}

static void desalocaAvanca(void *dado){
    Avanca *a=(Avanca*)dado;
    if(a!=NULL)
        free(a);
}

/* ---- VOLTA ---- */
typedef struct Volta {
    int recuo;
} Volta;

static Volta *criaVolta(int recuo){
    Volta *v=(Volta*)calloc(1,sizeof(Volta));
    v->recuo=recuo;
    return v;
}

static Volta *leVolta(){
    int recuo;
    scanf("%d",&recuo);
    return criaVolta(recuo);
}

static int executaVolta(void *dado,Jogador *j){
    Volta *v=(Volta*)dado;
    return -v->recuo;
}

static void imprimeVolta(void *dado){
    Volta *v=(Volta*)dado;
    printf("VOLTA %d",v->recuo);
}

static void desalocaVolta(void *dado){
    Volta *v=(Volta*)dado;
    if(v!=NULL)
        free(v);
}

/* ---- VAZIA ---- */
typedef struct Vazia {
    int nada;
} Vazia;

static Vazia *criaVazia(){
    Vazia *v=(Vazia*)calloc(1,sizeof(Vazia));
    return v;
}

static Vazia *leVazia(){
    return criaVazia();
}

static int executaVazia(void *dado,Jogador *j){
    return 0;
}

static void imprimeVazia(void *dado){
    printf("VAZIA");
}

static void desalocaVazia(void *dado){
    if(dado!=NULL){
        free(dado);
    }
}

/* ======================= Fim das acoes ================================= */


static int resolveDisputa(Mapa *m, Jogador *joga, int pos) {
    Jogador *oponente = obtemOcupanteMapa(m, pos);
    int venceu = venceDisputaJogador(joga, oponente);
    if (venceu == 1) {
        retiraJogadorMapa(m, joga);
        recuaJogadorMapa(m, oponente, pos);
        moveJogadorMapa(m, joga, pos);
        incrementaDisputasVencidasJogador(joga);
        return 1;
    } else {
        retiraJogadorMapa(m, joga);
        recuaJogadorMapa(m, joga, pos);
        incrementaDisputasVencidasJogador(oponente);
        return 0;
    }
}

int main() {
    char indice[MAX_TAM_INDICE];
    Mapa *m = NULL;

    while (scanf("%s", indice) == 1) {
        if (!strcmp(indice, "INICIO")) {
            scanf("%*s");
            m = criaMapa();
        } else if (!strcmp(indice, "OURO")) {
            Ouro *o = leOuro();
            insereCelulaMapa(m, o, executaOuro, imprimeOuro, desalocaOuro);
        } else if (!strcmp(indice, "ITEM")) {
            Item *i = leItem();
            insereCelulaMapa(m, i, executaItem, imprimeItem, desalocaItem);
        } else if (!strcmp(indice, "MONSTRO")) {
            Monstro *mons = leMonstro();
            insereCelulaMapa(m, mons, executaMonstro, imprimeMonstro, desalocaMonstro);
        } else if (!strcmp(indice, "VAZIA")) {
            Vazia *vaz = leVazia();
            insereCelulaMapa(m, vaz, executaVazia, imprimeVazia, desalocaVazia);
        } else if (!strcmp(indice, "AVANCA")) {
            Avanca *a = leAvanca();
            insereCelulaMapa(m, a, executaAvanca, imprimeAvanca, desalocaAvanca);
        } else if (!strcmp(indice, "VOLTA")) {
            Volta *v = leVolta();
            insereCelulaMapa(m, v, executaVolta, imprimeVolta, desalocaVolta);
        } else if (!strcmp(indice, "FIM")) {
            scanf("%*s");
            break;
        }
    }

    int nJogadores = 0, ganhou = 0, numVence = 0, turno = 0, vezes = 0;
    Jogador **jogadores = NULL;

    while (scanf(" %s", indice) == 1) {
        if (strcmp(indice, "F") == 0) {
            break;
        } else if (strcmp(indice, "J") == 0) {
            Jogador *novo = leJogador();
            int duplicado = 0;
            for (int i = 0; i < nJogadores; i++) {
                if (comparaNomeJogador(jogadores[i], obtemNomeJogador(novo)) == 1) {
                    duplicado = 1;
                    break;
                }
            }
            if (duplicado) {
                desalocaJogador(novo);
            } else {
                jogadores = realloc(jogadores, sizeof(Jogador *) * (nJogadores + 1));
                jogadores[nJogadores] = novo;
                nJogadores++;
            }
        } else if (strcmp(indice, "E") == 0) {
            scanf("%s", indice);
            int nJogadas = 0, nDisputas = 0, nMonstDerr = 0;
            for (int b = 0; b < nJogadores; b++) {
                nMonstDerr += obtemMonstrosDerrotadosJogador(jogadores[b]);
                nJogadas += obtemJogadasJogador(jogadores[b]);
                nDisputas += obtemDisputasVencidasJogador(jogadores[b]);
            }
            if (strcmp(indice, "ESTADO") == 0) {
                printf("=========== ESTADO ============\n");
                printf("[INICIO]");
                int primeiroInicio = 1;
                for (int i = 0; i < nJogadores; i++) {
                    if (obtemPosicaoJogador(jogadores[i]) == 0) {
                        printf(primeiroInicio ? " <- %s" : ", %s", obtemNomeJogador(jogadores[i]));
                        primeiroInicio = 0;
                    }
                }
                printf("\n");
                imprimeCelulasMapa(m);
                printf("[FIM]");
                if (ganhou == 1) {
                    printf(" <- %s", obtemNomeJogador(jogadores[numVence]));
                }
                printf("\n");
                printf("-------------------------------\n");
                for (int i = 0; i < nJogadores; i++) {
                    printEstadoJogador(jogadores[i]);
                }
                printf("- Situacao: ");
                if (ganhou == 1) {
                    printf("VENCEDOR %s\n", obtemNomeJogador(jogadores[numVence]));
                } else {
                    printf("EM ANDAMENTO\n");
                }
                printf("===============================\n");
            } else if (strcmp(indice, "RELATORIO") == 0) {
                
                printf("========= RELATORIO ===========\n");
                printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(m));
                printf("- Jogadores: %d\n", nJogadores);
                printf("- Jogadas totais: %d\n", nJogadas);
                printf("- Disputas: %d\n", nDisputas);
                printf("- Monstros derrotados: %d\n", nMonstDerr);
                if (ganhou == 1) {
                    printf("- Situacao: VENCEDOR %s\n", obtemNomeJogador(jogadores[numVence]));
                } else {
                    printf("- Situacao: EM ANDAMENTO\n");
                }
                printf("-------------------------------\n");
                for (int i = 0; i < nJogadores; i++) {
                    printRelatorioJogador(jogadores[i]);
                }
                printf("===============================\n");
            } else if (strcmp(indice, "RANKING") == 0) {
                printf("=========== RANKING ===========\n");
                if (nJogadores > 0) {
                    Jogador **ranking = malloc(sizeof(Jogador *) * nJogadores);
                    for(int i=0;i<nJogadores;i++){
                        ranking[i]=copiaJogador(jogadores[i]);
                    }
                    qsort(ranking, nJogadores, sizeof(Jogador *), comparaOrdJogador);
                    for (int i = 0; i < nJogadores; i++) {
                        printRankingJogador(ranking[i], i + 1);
                        desalocaJogador(ranking[i]);
                    }
                    free(ranking);
                }
                printf("===============================\n");
            }
        } else if (strcmp(indice, "ROLAGEM") == 0) {
            scanf("%d", &vezes);
            if (ganhou == 0 && nJogadores > 0) {
                for (int i = 0; i < vezes; i++) {
                    if (turno >= nJogadores) {
                        turno = 0;
                    }
                    int dado = RolaDado();
                    Jogador *joga = jogadores[turno];
                    incrementaJogadasJogador(joga);
                    int pos = obtemPosicaoJogador(joga) + dado;
                    if (pos >= obtemPosicaoFimMapa(m)) {
                        pos = obtemPosicaoFimMapa(m);
                        ganhou = 1;
                        numVence = turno;
                        moveJogadorMapa(m, joga, pos);
                        break;
                    }
                    int atual = pos;
                    int chegou = 1;
                    Celula *celu = obtemCelulaMapa(m, atual);
                    if (estaOcupadaCelula(celu) == 1) {
                        chegou = resolveDisputa(m, joga, atual);
                    } else {
                        moveJogadorMapa(m, joga, atual);
                    }

                    while (chegou) {
                        celu = obtemCelulaMapa(m, atual);
                        int res = executaAcaoCelula(celu, joga);
                        if (res == 0) {
                            break;
                        }
                        if (res == RECUO_CELULA) {
                            recuaJogadorMapa(m, joga, atual);
                            break;
                        }
                        int novaPos = atual + res;
                        if (novaPos < 0) {
                            novaPos = 0;
                        }
                        if (novaPos >= obtemPosicaoFimMapa(m)) {
                            ganhou = 1;
                            numVence = turno;
                            moveJogadorMapa(m, joga, obtemPosicaoFimMapa(m));
                            break;
                        }
                        if (novaPos == 0) {
                            moveJogadorMapa(m, joga, 0);
                            break;
                        }
                        Celula *novaCel = obtemCelulaMapa(m, novaPos);
                        atual = novaPos;
                        if (estaOcupadaCelula(novaCel) == 1) {
                            chegou = resolveDisputa(m, joga, atual);
                        } else {
                            moveJogadorMapa(m, joga, atual);
                        }
                        break; /* o deslocamento de AVANCA/VOLTA nao dispara nova acao */
                    }

                    if (ganhou == 1) {
                        break;
                    }
                    turno++;
                }
            }
        }
    }

    for (int i = 0; i < nJogadores; i++) {
        desalocaJogador(jogadores[i]);
    }
    free(jogadores);
    desalocaMapa(m);
    return 0;
}