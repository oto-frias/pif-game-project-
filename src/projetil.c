#include <stdlib.h>
#include <math.h>
#include "arena.h"
#include "projetil.h"

/* atira no inimigo mais proximo. Devolve 1 se atirou */
int atirar(Jogador *j, Inimigo *inimigos, Projetil **tiros) {
    Inimigo *aux;
    Inimigo *alvo = NULL;
    float menor = 1000000.0f;

    for (aux = inimigos; aux != NULL; aux = aux->prox) {
        float ddx = aux->x - j->x;
        float ddy = aux->y - j->y;
        float dist = ddx * ddx + ddy * ddy;
        if (dist < menor) {
            menor = dist;
            alvo = aux;
        }
    }
    if (alvo == NULL) return 0;

    float vx = alvo->x - j->x;
    float vy = alvo->y - j->y;
    float tam = sqrtf(vx * vx + vy * vy);
    if (tam < 0.01f) return 0;

    Projetil *novo = (Projetil *) malloc(sizeof(Projetil));
    if (novo == NULL) return 0;

    novo->x = j->x;
    novo->y = j->y;
    novo->dx = vx / tam;   /* vetor de tamanho 1 apontando pro alvo */
    novo->dy = vy / tam;
    novo->prox = *tiros;
    *tiros = novo;
    return 1;
}

void atualizarProjeteis(Projetil **tiros, char arena[ALTURA][LARGURA], float dt) {
    Projetil *aux = *tiros;
    Projetil *anterior = NULL;

    while (aux != NULL) {
        aux->x += aux->dx * VEL_TIRO * dt;
        aux->y += aux->dy * VEL_TIRO * dt;

        if (colideParede(arena, aux->x, aux->y, 0.05f)) {
            /* bateu na parede: remove da lista */
            Projetil *morto = aux;
            if (anterior == NULL)
                *tiros = aux->prox;
            else
                anterior->prox = aux->prox;
            aux = aux->prox;
            free(morto);
        } else {
            anterior = aux;
            aux = aux->prox;
        }
    }
}
