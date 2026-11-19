#ifndef JOGADOR_H
#define JOGADOR_H

#include "tipos.h"

void moverJogador(Jogador *j, char arena[ALTURA][LARGURA], float dt);
void subirNivel(Jogador *j);
float intervaloTiro(int nivel);

#endif
