#include "arena.h"

void criarArena(char arena[ALTURA][LARGURA]) {
    int i, k;

    for (i = 0; i < ALTURA; i++) {
        for (k = 0; k < LARGURA; k++) {
            if (i == 0 || i == ALTURA - 1 || k == 0 || k == LARGURA - 1)
                arena[i][k] = '#';
            else
                arena[i][k] = ' ';
        }
    }

    /* alguns obstaculos fixos */
    for (k = 6; k < 11; k++) arena[5][k] = '#';
    for (k = 19; k < 25; k++) arena[13][k] = '#';
    for (i = 9; i < 15; i++) arena[i][8] = '#';
    for (i = 4; i < 9; i++) arena[i][22] = '#';
}

/* ve se um quadradinho de lado 2*raio centrado em (x,y) encosta em parede */
int colideParede(char arena[ALTURA][LARGURA], float x, float y, float raio) {
    int c;
    float cantos[4][2] = {{-raio, -raio}, {raio, -raio}, {-raio, raio}, {raio, raio}};

    for (c = 0; c < 4; c++) {
        float px = x + cantos[c][0];
        float py = y + cantos[c][1];
        if (px < 0 || py < 0) return 1;
        int cx = (int) px;
        int cy = (int) py;
        if (cx >= LARGURA || cy >= ALTURA) return 1;
        if (arena[cy][cx] == '#') return 1;
    }
    return 0;
}

/* anda um eixo de cada vez, assim desliza na parede em vez de travar */
void andarComColisao(char arena[ALTURA][LARGURA], float *x, float *y, float dx, float dy, float raio) {
    if (!colideParede(arena, *x + dx, *y, raio)) *x += dx;
    if (!colideParede(arena, *x, *y + dy, raio)) *y += dy;
}
