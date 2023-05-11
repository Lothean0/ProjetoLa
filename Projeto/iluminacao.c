#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "mapa.h"

// o ncurses usa ints para fazer pares de cores lolmao
#define Visivel 1
#define Nao_Visivel 2
#define Visto 3

void inicializar_cor(void)
{
    start_color();
    init_pair(Visivel, COLOR_WHITE, COLOR_BLACK);
    init_pair(Nao_Visivel, COLOR_BLACK, COLOR_BLACK);
    init_pair(Visto, COLOR_CYAN, COLOR_BLACK);
}

void colorir(Player *jogador)
{
    jogador->cor = COLOR_PAIR(Visto);
}

void colorirm(Mapa *mapa)
{
    if (mapa->visao == 1)
    {
        mapa->cor = COLOR_PAIR(Visivel);
    }
    else if (mapa->visao == 0)
    {
        mapa->cor = COLOR_PAIR(Nao_Visivel);
    }
    else
    {
        mapa->cor = COLOR_PAIR(Visto);
    }
}
