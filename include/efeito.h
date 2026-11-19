#ifndef EFEITO_H
#define EFEITO_H

#include "tipos.h"

#define FRAMES 4                    /* quadros de cada animacao */
#define TEMPO_QUADRO_EXPLOSAO 0.08f /* segundos em cada quadro */

void criarEfeito(Efeito **efeitos, float x, float y);
void atualizarEfeitos(Efeito **efeitos, float dt);

#endif
