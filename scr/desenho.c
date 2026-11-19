#include <stdlib.h>
#include "raylib.h"
#include "desenho.h"
#include "sprites.h"
#include "ranking.h"

static void textoCentralizado(const char *texto, int y, int tamanho, Color cor) {
    DrawText(texto, (TELA_L - MeasureText(texto, tamanho)) / 2, y, tamanho, cor);
}

void desenharJogo(char arena[ALTURA][LARGURA], Jogador *j, Inimigo *inimigos, Projetil *tiros, Efeito *efeitos, int segundos, double tempo) {
    int i, k;
    Inimigo *ini;
    Projetil *t;
    Efeito *ef;

    ClearBackground(BLACK);

    /* chao e paredes */
    for (i = 0; i < ALTURA; i++) {
        for (k = 0; k < LARGURA; k++) {
            Texture2D tex = (arena[i][k] == '#') ? spriteParede() : spriteChao();
            if (tex.id != 0)
                DrawTexture(tex, k * TILE, OFF_Y + i * TILE, WHITE);
            else
                DrawRectangle(k * TILE, OFF_Y + i * TILE, TILE, TILE, arena[i][k] == '#' ? GRAY : DARKGRAY);
        }
    }

    for (ef = efeitos; ef != NULL; ef = ef->prox) {
        int frame = (int)(ef->tempo / TEMPO_QUADRO_EXPLOSAO);
        desenharSprite(spriteExplosao(frame), ef->x, ef->y, 1, ORANGE);
    }

    for (ini = inimigos; ini != NULL; ini = ini->prox) {
        int frame = (int)(tempo * 8 + ini->anim);
        int virado = (ini->x > j->x) ? -1 : 1;   /* olha pro jogador */
        if (ini->tipo == 1)
            desenharSprite(spriteInimigo(frame), ini->x, ini->y, virado, RED);
        else
            desenharSprite(spriteTanque(frame), ini->x, ini->y, virado, PURPLE);
    }

    for (t = tiros; t != NULL; t = t->prox)
        desenharSprite(spriteTiro((int)(tempo * 16)), t->x, t->y, 1, YELLOW);

    /* pisca quando acabou de levar dano */
    if (j->invencivel <= 0 || ((int)(tempo * 20)) % 2 == 0)
        desenharSprite(spriteJogador((int)(tempo * 8)), j->x, j->y, j->virado, SKYBLUE);

    /* HUD */
    DrawRectangle(0, 0, TELA_L, OFF_Y, (Color){20, 20, 30, 255});
    for (i = 0; i < VIDA_MAX; i++)
        DrawRectangle(10 + i * 18, 10, 14, 20, i < j->vida ? RED : (Color){70, 30, 30, 255});

    DrawText(TextFormat("Nivel %d", j->nivel), 215, 10, 20, WHITE);
    DrawRectangle(310, 14, 150, 12, (Color){50, 50, 70, 255});
    DrawRectangle(310, 14, 150 * j->xp / (j->nivel * 5), 12, SKYBLUE);
    DrawText(TextFormat("Pontos %d", j->pontos), 500, 10, 20, GOLD);
    DrawText(TextFormat("Tempo %ds", segundos), 720, 10, 20, WHITE);
}

void desenharTitulo(void) {
    ClearBackground((Color){20, 20, 30, 255});
    textoCentralizado("VAMPIRE SURVIVOR", 200, 60, RED);
    textoCentralizado("PIF  -  versao em C com raylib", 270, 24, LIGHTGRAY);
    textoCentralizado("WASD ou setas: mover   |   o tiro e automatico", 380, 24, WHITE);
    textoCentralizado("Aperte ENTER para jogar", 460, 30, GOLD);
}

void desenharFim(Jogador *j, int segundos) {
    struct Score lista[MAX_RANK];
    int total = lerRanking(lista);
    int i;

    ClearBackground((Color){20, 20, 30, 255});
    textoCentralizado("GAME OVER", 60, 60, RED);
    textoCentralizado(TextFormat("Pontos: %d   Nivel: %d   Tempo: %ds", j->pontos, j->nivel, segundos), 140, 26, WHITE);

    textoCentralizado("TOP 5", 220, 30, GOLD);
    for (i = 0; i < total; i++)
        textoCentralizado(TextFormat("%d.  %d pontos  -  %ds", i + 1, lista[i].pontos, lista[i].tempo), 270 + i * 36, 24, LIGHTGRAY);

    textoCentralizado("ENTER: jogar de novo   |   ESC: sair", 540, 24, WHITE);
}
