#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "acao_avanca.h"
#include "acao_item.h"
#include "acao_monstro.h"
#include "acao_ouro.h"
#include "acao_volta.h"
#include "dado.h"
#include "acao_vazia.h"

#define MAX_TAM_INDICE 21

static void resolveDisputa(Mapa *m, Jogador *joga, int pos) {
    Jogador *oponente = obtemOcupanteMapa(m, pos);
    int venceu = venceDisputaJogador(joga, oponente);
    if (venceu == 1) {
        retiraJogadorMapa(m, joga);
        recuaJogadorMapa(m, oponente, pos);
        moveJogadorMapa(m, joga, pos);
        incrementaDisputasVencidasJogador(joga);
    } else {
        recuaJogadorMapa(m, joga, pos);
        incrementaDisputasVencidasJogador(oponente);
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

            if (strcmp(indice, "ESTADO") == 0) {
                printf("=========== ESTADO ============\n");
                printf("[INICIO]");
                for (int i = 0; i < nJogadores; i++) {
                    if (obtemPosicaoJogador(jogadores[i]) == 0) {
                        printf(" <- %s", obtemNomeJogador(jogadores[i]));
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
                int nJogadas = 0, nDisputas = 0, nMonstDerr = 0;
                for (int b = 0; b < nJogadores; b++) {
                    nMonstDerr += obtemMonstrosDerrotadosJogador(jogadores[b]);
                    nJogadas += obtemJogadasJogador(jogadores[b]);
                    nDisputas += obtemDisputasVencidasJogador(jogadores[b]);
                }
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
                    memcpy(ranking, jogadores, sizeof(Jogador *) * nJogadores);
                    qsort(ranking, nJogadores, sizeof(Jogador *), comparaOrdJogador);
                    for (int i = 0; i < nJogadores; i++) {
                        printRankingJogador(ranking[i], i + 1);
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

                    Celula *celu = obtemCelulaMapa(m, pos);
                    if (estaOcupadaCelula(celu) == 1) {
                        resolveDisputa(m, joga, pos);
                    } else {
                        moveJogadorMapa(m, joga, pos);
                        int res = executaAcaoCelula(celu, joga);

                        if (res == RECUO_CELULA) {
                            recuaJogadorMapa(m, joga, pos);
                        } else if (res != 0) {
                            int novaPos = pos + res;
                            if (novaPos < 0) {
                                novaPos = 0;
                            }
                            if (novaPos >= obtemPosicaoFimMapa(m)) {
                                ganhou = 1;
                                numVence = turno;
                                moveJogadorMapa(m, joga, obtemPosicaoFimMapa(m));
                                break;
                            } else if (novaPos == 0) {
                                moveJogadorMapa(m, joga, 0);
                            } else {
                                Celula *novaCel = obtemCelulaMapa(m, novaPos);
                                if (estaOcupadaCelula(novaCel) == 1) {
                                    resolveDisputa(m, joga, novaPos);
                                } else {
                                    moveJogadorMapa(m, joga, novaPos);
                                }
                            }
                        }
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