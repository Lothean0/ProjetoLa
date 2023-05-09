#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "mapa.h"

void spawn(Player *jogador, int MaxY, int MaxX)
{
    // while(mvinch(jogador->coorY, jogador->coorX)=='#')
    {
        srand(time(NULL));
        jogador->coorY = rand() % MaxY + 2;
        jogador->coorX = rand() % MaxX + 2;
    }
}

int main(void)
{
    // inicializa o jogador
    Player jogador1;
    jogador1.coorX = 0;
    jogador1.coorY = 0;

    // cenas do stor
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    // inicializa a window e calcula a "resoluçao do ecra"
    WINDOW *win = initscr();
    inicializar_cor();
    colorir(&jogador1);
    curs_set(0);
    int MaxY, MaxX;
    getmaxyx(win, MaxY, MaxX);
    // nodelay(win,true);

    // cria uma box à volta da window
    //move(0, 0);
    //wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');

    // gerar mapa?
    Mapa mapa[MaxY][MaxX];
    
    int i, j;
    for(i = 0; i < MaxY; i++) {
        for(j = 0; j < MaxX; j++) {
            int chance = randomgen(); // sempre (0<=chance<100)
            if (chance < 45)
            {
                mapa[i][j].character = '#';
                mapa[i][j].distancia = 0;
            }
            else
            {
                mapa[i][j].character = '.';  // 55%
                mapa[i][j].distancia = 0;
            }
            /*mapa[i][j].character = '#'; //inicializa todo o mapa com paredes
            mapa[i][j].distancia = 0;*/
        }
    }
    //geracao(mapa, MaxY, MaxX);
    for (int ys = 0; ys < MaxY; ys++)
    {
        for (int xs = 0; xs < MaxX; xs++)
        {
            mvwprintw( win, ys, xs, "%c", mapa[ys][xs].character);
        }
    }

    // coloca o jogador numa posicao random do ecra
    spawn(&jogador1, MaxY, MaxX);
    mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);

    int w = 0; // parte do timer

    // ciclo while que corre enquanto a tecla q nao e premida
    while (1)
    {
        // pequeno timer
        move(2, 2);
        printw("(%d)", w);
        w++;

        // updates ao jogador
        mudarstate(&jogador1);
        move(jogador1.coorY, jogador1.coorX);
        mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
        refresh();
    }
    endwin();
    return 0;
}
