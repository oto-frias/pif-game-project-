#include <stdlib.h>
#include "colisoes.h"
#include "inimigo.h"
#include "jogador.h"
#include "efeito.h"

/* 1 se os dois pontos estao mais perto que "raio" */
static int perto(float x1, float y1, float x2, float y2, float raio) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return (dx * dx + dy * dy) < raio * raio;
}

void verificarColisoes(Jogador *j, Inimigo **inimigos, Projetil **tiros, Efeito **efeitos) {
    Projetil *t = *tiros;
    Projetil *anterior = NULL;
    Inimigo *ini;

    while (t != NULL) {
        Inimigo *alvo = NULL;

        for (ini = *inimigos; ini != NULL; ini = ini->prox) {
            if (perto(t->x, t->y, ini->x, ini->y, 0.5f)) {
                alvo = ini;
                break;
            }
        }

        if (alvo != NULL) {
            alvo->vida--;
            if (alvo->vida <= 0) {
                if (alvo->tipo == 1) { j->pontos += 10; j->xp += 1; }
                else                 { j->pontos += 30; j->xp += 3; }
                /* cria a explosao antes de liberar o inimigo (precisa da posicao dele) */
                criarEfeito(efeitos, alvo->x, alvo->y);
                removerInimigo(inimigos, alvo);
                subirNivel(j);
            }

            /* o tiro some quando acerta */
            Projetil *morto = t;
            if (anterior == NULL)
                *tiros = t->prox;
            else
                anterior->prox = t->prox;
            t = t->prox;
            free(morto);
        } else {
            anterior = t;
            t = t->prox;
        }
    }

    /* inimigo encostando no jogador */
    if (j->invencivel <= 0) {
        for (ini = *inimigos; ini != NULL; ini = ini->prox) {
            if (perto(ini->x, ini->y, j->x, j->y, 0.6f)) {
                j->vida--;
                j->invencivel = 1.0f;
                break;
            }
        }
    }
}
