#include"mapa.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Mapa{
    Celula **celulas;
    int nCelulas;
};

/**
 * @brief Aloca dinamicamente um mapa sem nenhuma célula (vetor de células NULL e quantidade 0)
 * @return Ponteiro para o mapa criado
 */
Mapa *criaMapa(){
    Mapa *m=(Mapa*)calloc(1,sizeof(Mapa));
    m->celulas=(Celula**)calloc(1,sizeof(Celula*));
    return m;
}

/**
 * @brief Cria uma célula com a ação e as funções de callback informadas (criaCelula), aumenta o
 * vetor de células do mapa em uma posição (realloc) e coloca a nova célula no final. A primeira
 * célula inserida corresponde à casa 1, a segunda à casa 2 e assim por diante.
 * @param m Mapa
 * @param acao Uma ação genérica (considerando que existe mais de um tipo de ação)
 * @param executa Função de callback que executa a ação sobre um jogador
 * @param imprime Função de callback que imprime a ação
 * @param desaloca Função de callback que desaloca a ação
 */
void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    m->celulas[m->nCelulas]=criaCelula(acao,executa,imprime,desaloca);
    m->nCelulas++;
    m->celulas=realloc(m->celulas,sizeof(Celula*)*(m->nCelulas+1));
}

/**
 * @brief Retorna a quantidade N de células informadas do mapa (sem contar Início e Fim)
 * @param m Mapa
 * @return Quantidade de células
 */
int obtemQtdCelulasMapa(Mapa *m){
    return m->nCelulas;
}

/**
 * @brief Retorna o número da casa do Fim do mapa, que é N + 1
 * @param m Mapa
 * @return Posição do Fim
 */
int obtemPosicaoFimMapa(Mapa *m){
    return m->nCelulas+1;
}

/**
 * @brief Retorna a célula correspondente à casa informada. Como as casas começam em 1, a casa
 * 'posicao' fica no índice 'posicao - 1' do vetor. Para o Início (0), o Fim (N + 1) ou qualquer
 * posição fora do intervalo de 1 a N, retorna NULL.
 * @param m Mapa
 * @param posicao Casa desejada (1 a N)
 * @return Célula da casa ou NULL se a posição for o Início, o Fim ou inválida
 */
Celula *obtemCelulaMapa(Mapa *m, int posicao){
    return m->celulas[posicao-1];
}

/**
 * @brief Retorna o jogador que ocupa a casa informada. Se a casa não for uma célula válida
 * (Início, Fim ou fora do mapa), retorna NULL, ou seja, o Início e o Fim nunca são considerados ocupados.
 * @param m Mapa
 * @param posicao Casa desejada
 * @return Jogador ocupante ou NULL
 */
Jogador *obtemOcupanteMapa(Mapa *m, int posicao){
    return obtemOcupanteCelula(m->celulas[posicao-1]);
}

/**
 * @brief Retira o jogador de sua célula atual, caso a célula exista e o ocupante dela seja esse
 * jogador. Não altera a posição armazenada no jogador.
 * @param m Mapa
 * @param j Jogador
 */
void retiraJogadorMapa(Mapa *m, Jogador *j){
    for(int i=0;i<m->nCelulas;i++){
        Jogador *jOcupante=obtemOcupanteCelula(m->celulas[i]);
        if(jOcupante!=NULL&&comparaOrdJogador(jOcupante,j)==0){
            defineOcupanteCelula(m->celulas[i],NULL);
            break;
        }
    }
}

/**
 * @brief Move o jogador para a casa informada: retira o jogador da célula atual (retiraJogadorMapa),
 * atualiza a posição do jogador e, se a nova casa for uma célula (1 a N), marca o jogador como seu
 * ocupante. Não verifica disputas nem executa ações.
 * @param m Mapa
 * @param j Jogador
 * @param posicao Casa de destino (0 a N + 1)
 */
void moveJogadorMapa(Mapa *m, Jogador *j, int posicao){
    retiraJogadorMapa(m,j);
    defineOcupanteCelula(m->celulas[posicao-1],j);
}

/**
 * @brief Aplica a regra de recuo: começando na casa 'origem - 1', vai voltando uma casa enquanto a
 * casa estiver ocupada e for maior que 0. O jogador é movido (moveJogadorMapa) para a primeira casa
 * livre encontrada ou para o Início (casa 0). O recuo não dispara ações nem disputas.
 * @param m Mapa
 * @param j Jogador que deve recuar
 * @param origem Casa a partir da qual o jogador recua (a casa em que ele estava)
 */
void recuaJogadorMapa(Mapa *m, Jogador *j, int origem){
    for(int i=origem-1;i>0;i--){
        moveJogadorMapa(m,j,i);
    }
}

/**
 * @brief Percorre as células do mapa, da casa 1 até a casa N, imprimindo cada uma com imprimeCelula
 * @param m Mapa
 */
void imprimeCelulasMapa(Mapa *m){
    for(int i=0;i<m->nCelulas;i++){
        imprimeCelula(m->celulas[i],i+1);
    }
}

/**
 * @brief Desaloca cada célula do mapa (desalocaCelula), o vetor de células e o próprio mapa.
 * Os jogadores ocupantes não são desalocados.
 * @param m Mapa
 */
void desalocaMapa(Mapa *m){
    for(int i=0;i<m->nCelulas;i++){
        desalocaCelula(m->celulas[i]);
    }
    free(m->celulas);
    free(m);
}