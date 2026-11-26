#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mapa {
    Celula **celulas;
    int nCelulas;
};

Mapa *criaMapa() {
    Mapa *m = (Mapa *)calloc(1, sizeof(Mapa));
    return m;
}

void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca) {
    m->celulas = realloc(m->celulas, sizeof(Celula *) * (m->nCelulas + 1));
    m->celulas[m->nCelulas] = criaCelula(acao, executa, imprime, desaloca);
    m->nCelulas++;
}

int obtemQtdCelulasMapa(Mapa *m) {
    return m->nCelulas;
}

int obtemPosicaoFimMapa(Mapa *m) {
    return m->nCelulas + 1;
}

Celula *obtemCelulaMapa(Mapa *m, int posicao) {
    if (m == NULL || posicao < 1 || posicao > m->nCelulas) {
        return NULL;
    }
    return m->celulas[posicao - 1];
}

Jogador *obtemOcupanteMapa(Mapa *m, int posicao) {
    if (m != NULL && posicao >= 1 && posicao <= m->nCelulas) {
        return obtemOcupanteCelula(m->celulas[posicao - 1]);
    }
    return NULL;
}

void retiraJogadorMapa(Mapa *m, Jogador *j) {
    if (m == NULL || j == NULL) return;
    for (int i = 0; i < m->nCelulas; i++) {
        Jogador *j2 = obtemOcupanteCelula(m->celulas[i]);
        if (j2 != NULL && j2 == j) {
            defineOcupanteCelula(m->celulas[i], NULL);
            break;
        }
    }
}

void moveJogadorMapa(Mapa *m, Jogador *j, int posicao) {
    retiraJogadorMapa(m, j);
    definePosicaoJogador(j, posicao);
    if (posicao >= 1 && posicao <= m->nCelulas) {
        defineOcupanteCelula(m->celulas[posicao - 1], j);
    }
}

void recuaJogadorMapa(Mapa *m, Jogador *j, int origem) {
    retiraJogadorMapa(m, j);
    int pos = origem - 1;
    while (pos > 0 && obtemOcupanteMapa(m, pos) != NULL) {
        pos--;
    }
    if (pos < 0) {
        pos = 0;
    }
    moveJogadorMapa(m, j, pos);
}

void imprimeCelulasMapa(Mapa *m) {
    for (int i = 0; i < m->nCelulas; i++) {
        imprimeCelula(m->celulas[i], i + 1);
    }
}

void desalocaMapa(Mapa *m) {
    if (m != NULL) {
        for (int i = 0; i < m->nCelulas; i++) {
            desalocaCelula(m->celulas[i]);
        }
        free(m->celulas);
        free(m);
    }
}