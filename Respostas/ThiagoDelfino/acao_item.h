#ifndef _ACAO_ITEM_H_
#define _ACAO_ITEM_H_

#include"jogador.h"

#define MAX_TAM_NOME_ITEM 21

typedef struct Item Item;

Item *criaItem(char *nome,int preco, int bonus);

Item *leItem();

int executaItem(void *dado,Jogador *j);

void imprimeItem(void *dado);

void desalocaItem(void dado);

#endif