#include "raylib.h"
#include "arena.h"
#include "jogador.h"

void moverJogador(Jogador *j, char arena[ALTURA][LARGURA], float dt) {
    float dx = 0, dy = 0;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1;

    /* na diagonal nao pode andar mais rapido */
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    if (dx < 0) j->virado = -1;
    if (dx > 0) j->virado = 1;

    andarComColisao(arena, &j->x, &j->y, dx * VEL_JOGADOR * dt, dy * VEL_JOGADOR * dt, 0.3f);
}

void subirNivel(Jogador *j) {
    while (j->xp >= j->nivel * 5) {
        j->xp -= j->nivel * 5;
        j->nivel++;
        if (j->vida < VIDA_MAX) j->vida++;
    }
}

/* quanto maior o nivel, mais rapido atira  */
float intervaloTiro(int nivel) {
    float t = 0.75f - nivel * 0.05f;
    if (t < 0.2f) t = 0.2f;
    return t;
}
