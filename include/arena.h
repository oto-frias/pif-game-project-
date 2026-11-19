#ifndef ARENA_H
#define ARENA_H

#include "tipos.h"

void criarArena(char arena[ALTURA][LARGURA]);
int colideParede(char arena[ALTURA][LARGURA], float x, float y, float raio);
void andarComColisao(char arena[ALTURA][LARGURA], float *x, float *y, float dx, float dy, float raio);

#endif
