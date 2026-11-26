#ifndef _ACAO_VAZIA_H_
#define _ACAO_VAZIA_H_

#include"jogador.h"

typedef struct Vazia Vazia;

Vazia *criaVazia();

Vazia *leVazia();

int executaVazia(void *dado,Jogador *j);

void imprimeVazia(void *dado);

void desalocaVazia(void *dado);


#endif
