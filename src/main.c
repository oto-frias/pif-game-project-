/*
 * Vampire Survivors PIF - jogo em C com raylib
 * WASD ou setas: mover | o jogador atira sozinho no inimigo mais proximo
 * Rode ./vampire-survivors-pif de dentro da pasta do projeto (onde fica a pasta assets).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "tipos.h"
#include "arena.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "efeito.h"
#include "colisoes.h"
#include "desenho.h"
#include "ranking.h"
#include "sprites.h"

enum Estado { TITULO, JOGANDO, FIM };

static void liberarListas(Inimigo **inimigos, Projetil **tiros, Efeito **efeitos) {
    while (*inimigos != NULL) {
        Inimigo *aux = *inimigos;
        *inimigos = aux->prox;
        free(aux);
    }
    while (*tiros != NULL) {
        Projetil *aux = *tiros;
        *tiros = aux->prox;
        free(aux);
    }
    while (*efeitos != NULL) {
        Efeito *aux = *efeitos;
        *efeitos = aux->prox;
        free(aux);
    }
}

static void novaPartida(char arena[ALTURA][LARGURA], Jogador *j) {
    criarArena(arena);
    j->x = LARGURA / 2.0f;
    j->y = ALTURA / 2.0f;
    j->vida = VIDA_MAX;
    j->xp = 0;
    j->nivel = 1;
    j->pontos = 0;
    j->invencivel = 0;
    j->recarga = 0;
    j->virado = 1;
}

int main(void) {
    char arena[ALTURA][LARGURA];
    Jogador jogador;
    Inimigo *inimigos = NULL;
    Projetil *tiros = NULL;
    Efeito *efeitos = NULL;
    enum Estado estado = TITULO;
    float tempoPartida = 0;
    float contadorSpawn = 0;
    int segundos = 0;

    srand(time(NULL));
    novaPartida(arena, &jogador);

    InitWindow(TELA_L, TELA_A, "Vampire Survivors PIF");
    SetTargetFPS(60);
    carregarSprites();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;   /* evita pulo grande se a janela travar */

        if (estado == TITULO) {
            if (IsKeyPressed(KEY_ENTER)) estado = JOGANDO;
        }
        else if (estado == JOGANDO) {
            tempoPartida += dt;
            segundos = (int) tempoPartida;
            if (jogador.invencivel > 0) jogador.invencivel -= dt;

            moverJogador(&jogador, arena, dt);

            jogador.recarga -= dt;
            if (jogador.recarga <= 0 && atirar(&jogador, inimigos, &tiros))
                jogador.recarga = intervaloTiro(jogador.nivel);

            atualizarProjeteis(&tiros, arena, dt);
            verificarColisoes(&jogador, &inimigos, &tiros, &efeitos);
            moverInimigos(inimigos, &jogador, arena, dt);
            verificarColisoes(&jogador, &inimigos, &tiros, &efeitos);
            atualizarEfeitos(&efeitos, dt);

            contadorSpawn += dt;
            if (contadorSpawn >= intervaloSpawn(segundos)) {
                contadorSpawn = 0;
                spawnarInimigo(&inimigos, arena, segundos);
            }

            if (jogador.vida <= 0) {
                salvarScore(jogador.pontos, segundos);
                estado = FIM;
            }
        }
        else if (estado == FIM) {
            if (IsKeyPressed(KEY_ENTER)) {
                liberarListas(&inimigos, &tiros, &efeitos);
                novaPartida(arena, &jogador);
                tempoPartida = 0;
                contadorSpawn = 0;
                segundos = 0;
                estado = JOGANDO;
            }
        }

        BeginDrawing();
        if (estado == TITULO)
            desenharTitulo();
        else if (estado == JOGANDO)
            desenharJogo(arena, &jogador, inimigos, tiros, efeitos, segundos, GetTime());
        else
            desenharFim(&jogador, segundos);
        EndDrawing();
    }

    liberarListas(&inimigos, &tiros, &efeitos);
    descarregarSprites();
    CloseWindow();

    return 0;
}
