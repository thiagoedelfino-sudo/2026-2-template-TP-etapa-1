#ifndef _ACAO_VOLTA_H_
#define _ACAO_VOLTA_H_

#include"jogador.h"

typedef struct Volta Volta;

Volta *criaVolta(int recuo);

Volta *leVolta();

int executaVolta(void *dado,Jogador *j);

void imprimeVolta(void *dado);

void desalocaVolta(void dado);

#endif