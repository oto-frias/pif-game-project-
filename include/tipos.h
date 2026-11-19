#ifndef TIPOS_H
#define TIPOS_H

#define TILE 32                       /* tamanho de cada quadrado em pixels */
#define LARGURA 30                    /* arena em quadrados */
#define ALTURA 20
#define OFF_Y 40                      /* espaco do HUD no topo da janela */
#define TELA_L (LARGURA * TILE)
#define TELA_A (ALTURA * TILE + OFF_Y)

#define VIDA_MAX 10
#define MAX_RANK 5
#define VEL_JOGADOR 5.0f              /* quadrados por segundo */
#define VEL_TIRO 11.0f

/* posicoes sao em quadrados (float): x = 3.5 e o meio do quadrado 3 */

struct Jogador {
    float x, y;
    int vida;
    int xp;
    int nivel;
    int pontos;
    float invencivel;   /* segundos sem levar dano depois de ser atingido */
    float recarga;      /* segundos ate o proximo tiro */
    int virado;         /* 1 = olhando pra direita, -1 = esquerda */
};
typedef struct Jogador Jogador;

struct Inimigo {
    float x, y;
    int vida;
    int tipo;           /* 1 = normal, 2 = tanque */
    float anim;         /* deslocamento da animacao (cada um bate asa diferente) */
    struct Inimigo *prox;
};
typedef struct Inimigo Inimigo;

struct Projetil {
    float x, y;
    float dx, dy;       /* direcao (vetor de tamanho 1) */
    struct Projetil *prox;
};
typedef struct Projetil Projetil;

/* explosao que aparece quando um inimigo morre */
struct Efeito {
    float x, y;
    float tempo;        /* segundos desde que nasceu */
    struct Efeito *prox;
};
typedef struct Efeito Efeito;

struct Score {
    int pontos;
    int tempo;
};

#endif
