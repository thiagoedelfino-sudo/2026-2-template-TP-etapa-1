#include"celula.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Celula{
    void *acao;
    func_ptr_executa executa;
    func_ptr_desaloca desaloca;
    func_ptr_imprime imprime;
    Jogador *j;
};

/**
 * @brief Aloca dinamicamente uma célula e guarda nela o ponteiro para a ação genérica e as três
 * funções de callback recebidas. A célula é criada desocupada (ocupante NULL).
 * @param acao Uma ação genérica (considerando que existe mais de um tipo de ação)
 * @param executa Função de callback que executa a ação sobre um jogador
 * @param imprime Função de callback que imprime a ação
 * @param desaloca Função de callback que desaloca a ação
 * @return Uma célula inicializada e desocupada
 */
Celula *criaCelula(void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    Celula *c=(Celula*)calloc(1,sizeof(Celula));
    c->acao=acao;
    c->desaloca=desaloca;
    c->executa=executa;
    c->imprime=imprime;
    return c;
}

/**
 * @brief Executa a ação da célula sobre o jogador, chamando a função de callback 'executa' da célula
 * com a ação armazenada e o jogador, e repassa o valor retornado por ela.
 * @param c Célula inicializada
 * @param j Jogador que parou na célula
 * @return deslocamento resultante ou RECUO_CELULA
 */
int executaAcaoCelula(Celula *c, Jogador *j){
    return c->executa(c->acao,j);
}

/**
 * @brief Retorna o ponteiro genérico para a ação armazenada na célula
 * @param c Célula inicializada
 * @return ação genérica da Célula
 */
void *obtemAcaoCelula(Celula *c){
    return c->acao;
}

/**
 * @brief Retorna o jogador que ocupa a célula
 * @param c Célula inicializada
 * @return Jogador ocupante ou NULL se a célula estiver livre
 */
Jogador *obtemOcupanteCelula(Celula *c);

/**
 * @brief Define o jogador que ocupa a célula. A célula guarda apenas a referência ao jogador
 * (não é dona dele e não deve desalocá-lo).
 * @param c Célula inicializada
 * @param j Jogador ocupante (NULL para liberar a célula)
 */
void defineOcupanteCelula(Celula *c, Jogador *j);

/**
 * @brief Verifica se existe um jogador ocupando a célula
 * @param c Célula inicializada
 * @return 1 se estiver ocupada, 0 caso contrário
 */
int estaOcupadaCelula(Celula *c);

/**
 * @brief Imprime uma linha no formato do ESTADO: "[<posicao>] ", depois a ação (usando a função de
 * callback 'imprime' da célula), depois " <- <nome do ocupante>" se a célula estiver ocupada e,
 * por fim, a quebra de linha. Ex: "[2] MONSTRO GOBLIN (F:3 XP:10) <- CARLA"
 * @param c Célula inicializada
 * @param posicao Número da casa da célula no mapa
 */
void imprimeCelula(Celula *c, int posicao);

/**
 * @brief Desaloca a ação da célula (usando a função de callback 'desaloca') e depois a própria célula.
 * O ocupante não é desalocado.
 * @param c Célula a ser liberada
 */
void desalocaCelula(Celula *c);