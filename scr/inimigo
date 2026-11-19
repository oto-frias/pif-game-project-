#include <stdlib.h>
#include <math.h>
#include "arena.h"
#include "inimigo.h"

void spawnarInimigo(Inimigo **inimigos, char arena[ALTURA][LARGURA], int segundos) {
    int lado = rand() % 4;
    float x, y;

    if (lado == 0)      { x = 1.5f;           y = 1.5f + rand() % (ALTURA - 2); }
    else if (lado == 1) { x = LARGURA - 1.5f; y = 1.5f + rand() % (ALTURA - 2); }
    else if (lado == 2) { y = 1.5f;           x = 1.5f + rand() % (LARGURA - 2); }
    else                { y = ALTURA - 1.5f;  x = 1.5f + rand() % (LARGURA - 2); }

    if (arena[(int) y][(int) x] == '#') return;

    Inimigo *novo = (Inimigo *) malloc(sizeof(Inimigo));
    if (novo == NULL) return;

    novo->x = x;
    novo->y = y;
    novo->anim = (float)(rand() % 4);
    /* depois de 20 segundos comecam a aparecer tanques */
    if (segundos > 20 && rand() % 4 == 0) {
        novo->tipo = 2;
        novo->vida = 3;
    } else {
        novo->tipo = 1;
        novo->vida = 1;
    }

    novo->prox = *inimigos;
    *inimigos = novo;
}

/* tempo entre um spawn e outro, diminui com o passar do jogo */
float intervaloSpawn(int segundos) {
    float t = 1.6f - segundos * 0.012f;
    if (t < 0.35f) t = 0.35f;
    return t;
}

void moverInimigos(Inimigo *inimigos, Jogador *j, char arena[ALTURA][LARGURA], float dt) {
    Inimigo *aux;

    for (aux = inimigos; aux != NULL; aux = aux->prox) {
        float vel = (aux->tipo == 1) ? 1.7f : 1.0f;   /* tanque e mais lento */

        /* direcao do inimigo ate o jogador */
        float vx = j->x - aux->x;
        float vy = j->y - aux->y;
        float dist = sqrtf(vx * vx + vy * vy);
        if (dist < 0.01f) continue;

        andarComColisao(arena, &aux->x, &aux->y, vx / dist * vel * dt, vy / dist * vel * dt, 0.3f);
    }
}

void removerInimigo(Inimigo **inimigos, Inimigo *alvo) {
    Inimigo *aux = *inimigos;
    Inimigo *anterior = NULL;

    while (aux != NULL && aux != alvo) {
        anterior = aux;
        aux = aux->prox;
    }
    if (aux == NULL) return;

    /* tira o no da lista antes de dar free */
    if (anterior == NULL)
        *inimigos = aux->prox;
    else
        anterior->prox = aux->prox;

    free(aux);
}
