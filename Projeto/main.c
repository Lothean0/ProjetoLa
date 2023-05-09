#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"

typedef struct mapa
{
    char character;
    int luz; //??? ns
    int distancia;
}Mapa;

void spawn(Player *jogador, int MaxY, int MaxX)
{
    //while(mvinch(jogador->coorY, jogador->coorX)=='#')
    {
        srand(time(NULL));
        jogador->coorY = rand() % MaxY + 2;
        jogador->coorX = rand() % MaxX + 2;
    }
}

int main(void)
{
    //inicializa o jogador
    Player jogador1;
    jogador1.coorX=0;
    jogador1.coorY=0;

    //cenas do stor
    cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

    //inicializa a window e calcula a "resoluçao do ecra"
    WINDOW *win = initscr();
    curs_set(0);
    int MaxY,MaxX;
    getmaxyx(win,MaxY,MaxX);
    //nodelay(win,true); 

    //cria uma box à volta da window
    move(0,0);
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');

    //gerar mapa?
    //Mapa mapa[MaxY][MaxX];
    //gerar_mapa(mapa);

    
    //coloca o jogador numa posicao random do ecra
    spawn(&jogador1,MaxY,MaxX);
    mvaddch(jogador1.coorY,jogador1.coorX,'@' | A_BOLD);

    int w=0; //parte do timer

    //ciclo while que corre enquanto a tecla q nao e premida
    while(1)
    {
        //pequeno timer
        move( 2, 2);
        printw("(%d)",w);
        w++;

        //updates ao jogador
        mudarstate(&jogador1);
        move(jogador1.coorY,jogador1.coorX);
        mvaddch(jogador1.coorY,jogador1.coorX,'@' | A_BOLD);
        refresh();

    }
    endwin();
    return 0;
}
