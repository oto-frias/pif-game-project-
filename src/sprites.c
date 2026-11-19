#include <stdio.h>
#include "sprites.h"
#include "tipos.h"

static Texture2D texJogador[FRAMES];
static Texture2D texInimigo[FRAMES];
static Texture2D texTanque[FRAMES];
static Texture2D texTiro[FRAMES];
static Texture2D texExplosao[FRAMES];
static Texture2D texChao;
static Texture2D texParede;

/* carrega assets/<nome>_f0.png, _f1.png ... */
static void carregarAnim(const char *nome, Texture2D frames[]) {
    int i;
    char caminho[100];

    for (i = 0; i < FRAMES; i++) {
        sprintf(caminho, "assets/%s_f%d.png", nome, i);
        frames[i] = LoadTexture(caminho);
    }
}

static void liberarAnim(Texture2D frames[]) {
    int i;
    for (i = 0; i < FRAMES; i++)
        if (frames[i].id != 0) UnloadTexture(frames[i]);
}

/* so pode ser chamada depois do InitWindow */
void carregarSprites(void) {
    carregarAnim("jogador_idle_anim", texJogador);
    carregarAnim("inimigo_run_anim", texInimigo);
    carregarAnim("tanque_run_anim", texTanque);
    carregarAnim("tiro_anim", texTiro);
    carregarAnim("explosao_anim", texExplosao);
    texChao = LoadTexture("assets/chao.png");
    texParede = LoadTexture("assets/parede.png");
}

void descarregarSprites(void) {
    liberarAnim(texJogador);
    liberarAnim(texInimigo);
    liberarAnim(texTanque);
    liberarAnim(texTiro);
    liberarAnim(texExplosao);
    if (texChao.id != 0) UnloadTexture(texChao);
    if (texParede.id != 0) UnloadTexture(texParede);
}

Texture2D spriteJogador(int frame)   { return texJogador[frame % FRAMES]; }
Texture2D spriteInimigo(int frame)   { return texInimigo[frame % FRAMES]; }
Texture2D spriteTanque(int frame)    { return texTanque[frame % FRAMES]; }
Texture2D spriteTiro(int frame)      { return texTiro[frame % FRAMES]; }
Texture2D spriteExplosao(int frame)  { return texExplosao[frame % FRAMES]; }
Texture2D spriteChao(void)           { return texChao; }
Texture2D spriteParede(void)         { return texParede; }

void desenharSprite(Texture2D tex, float x, float y, int virado, Color corReserva) {
    int px = (int)((x - 0.5f) * TILE);
    int py = OFF_Y + (int)((y - 0.5f) * TILE);

    if (tex.id == 0) {
        DrawRectangle(px + 4, py + 4, TILE - 8, TILE - 8, corReserva);
        return;
    }

    Rectangle origem = {0, 0, (float) tex.width, (float) tex.height};
    if (virado < 0) origem.width = -origem.width;   /* largura negativa espelha */
    Vector2 pos = {(float) px, (float) py};
    DrawTextureRec(tex, origem, pos, WHITE);
}
