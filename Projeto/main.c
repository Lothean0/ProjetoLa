#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "movimento.c"

void spawn(Player *jogador, int MaxY, int MaxX)
{
    srand(time(NULL));
    jogador->coorY = rand() % MaxY + 2;
    jogador->coorX = rand() % MaxX - 2;
}

int main()
{
    Player jogador1 = {0,0};
    WINDOW *win = initscr();
    int MaxY,MaxX;
    getmaxyx(win,MaxY,MaxX);
    refresh();
    spawn(&jogador1,MaxY,MaxX);
    mvaddch(jogador1.coorY,jogador1.coorX,'@' | A_BOLD);
    refresh();
    mudarstate(jogador1);
    endwin();
    return 0;
}