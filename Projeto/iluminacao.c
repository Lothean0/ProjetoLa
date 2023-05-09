#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "player.h"

// o ncurses usa ints para fazer pares de cores lolmao
#define Visivel 1
#define Nao_Visivel 2

void inicializar_cor()
{
    if (has_colors())
    {
        start_color();
        init_pair(Visivel, COLOR_RED, COLOR_BLACK);
        init_pair(Nao_Visivel, COLOR_BLACK, COLOR_BLACK);
    }
}

void colorir(Player *jogador)
{
    jogador->cor = COLOR_PAIR(Visivel);
}
