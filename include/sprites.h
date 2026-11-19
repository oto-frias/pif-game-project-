#ifndef SPRITES_H
#define SPRITES_H

#include "raylib.h"
#include "efeito.h"   /* FRAMES */

void carregarSprites(void);
void descarregarSprites(void);

Texture2D spriteJogador(int frame);
Texture2D spriteInimigo(int frame);
Texture2D spriteTanque(int frame);
Texture2D spriteTiro(int frame);
Texture2D spriteExplosao(int frame);
Texture2D spriteChao(void);
Texture2D spriteParede(void);

/* desenha uma textura centralizada em (x,y), medidos em quadrados.
   virado = -1 espelha a imagem. Se a textura nao carregou, desenha um quadrado colorido */
void desenharSprite(Texture2D tex, float x, float y, int virado, Color corReserva);

#endif
