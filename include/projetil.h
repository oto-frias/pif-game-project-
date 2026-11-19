#ifndef PROJETIL_H
#define PROJETIL_H

#include "tipos.h"

int atirar(Jogador *j, Inimigo *inimigos, Projetil **tiros);
void atualizarProjeteis(Projetil **tiros, char arena[ALTURA][LARGURA], float dt);

#endif
