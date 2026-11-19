#ifndef DESENHO_H
#define DESENHO_H

#include "tipos.h"

void desenharJogo(char arena[ALTURA][LARGURA], Jogador *j, Inimigo *inimigos, Projetil *tiros, Efeito *efeitos, int segundos, double tempo);
void desenharTitulo(void);
void desenharFim(Jogador *j, int segundos);

#endif
