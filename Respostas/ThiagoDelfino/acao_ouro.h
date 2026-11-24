#ifndef _ACAO_OURO_H_
#define _ACAO_OURO_H_
#include"jogador.h"

typedef struct Ouro Ouro;

Ouro *criaOuro(int moedas);

Ouro *leOuro();

int executaOuro(void *dado,Jogador *j);

void imprimeOuro(void *dado);

void desalocaOuro(void dado);

#endif