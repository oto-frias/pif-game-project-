#include <stdlib.h>
#include "efeito.h"

void criarEfeito(Efeito **efeitos, float x, float y) {
    Efeito *novo = (Efeito *) malloc(sizeof(Efeito));
    if (novo == NULL) return;

    novo->x = x;
    novo->y = y;
    novo->tempo = 0;
    novo->prox = *efeitos;
    *efeitos = novo;
}

void atualizarEfeitos(Efeito **efeitos, float dt) {
    Efeito *aux = *efeitos;
    Efeito *anterior = NULL;

    while (aux != NULL) {
        aux->tempo += dt;

        if (aux->tempo >= FRAMES * TEMPO_QUADRO_EXPLOSAO) {
            /* acabou a animacao: tira da lista e libera */
            Efeito *morto = aux;
            if (anterior == NULL)
                *efeitos = aux->prox;
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
