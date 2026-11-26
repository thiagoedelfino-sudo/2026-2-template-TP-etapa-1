#ifndef _ACAO_AVANCA_H_
#define _ACAO_AVANCA_H_

#include"jogador.h"

typedef struct Avanca Avanca;

Avanca *criaAvanca(int avanco);

Avanca *leAvanca();

int executaAvanca(void *dado,Jogador *j);

void imprimeAvanca(void *dado);

void desalocaAvanca(void *dado);

#endif