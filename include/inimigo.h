#ifndef INIMIGO_H
#define INIMIGO_H

#include "tipos.h"

void spawnarInimigo(Inimigo **inimigos, char arena[ALTURA][LARGURA], int segundos);
float intervaloSpawn(int segundos);
void moverInimigos(Inimigo *inimigos, Jogador *j, char arena[ALTURA][LARGURA], float dt);
void removerInimigo(Inimigo **inimigos, Inimigo *alvo);

#endif
