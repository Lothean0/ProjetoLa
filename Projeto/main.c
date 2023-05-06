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

int main(void)
{
    //inicializa o jogoador
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
    int MaxY,MaxX;
    getmaxyx(win,MaxY,MaxX);

    //cria uma box à volta da window
    move(0,0);
    box(win, '|', '-');
    refresh();
    
    
    //cria uma box no meio do ecra
    /*int meioY = MaxY/2;
    int meioX = MaxX/2;
    mvprintw(meioY,meioX,"################################################");
    mvprintw(meioY + 1,meioX,"#..............................................#");
    mvprintw(meioY + 2,meioX,"#.................................#............#");
    mvprintw(meioY + 3,meioX,"#.................................#............#");
    mvprintw(meioY + 4,meioX,"#.................................#............#");
    mvprintw(meioY + 5,meioX,"#.................................#............#");
    mvprintw(meioY + 6,meioX,"#..............................................#");
    mvprintw(meioY + 7,meioX,"################################################");*/
    
    //coloca o jogador numa posicao random do ecra
    spawn(&jogador1,MaxY,MaxX);
    move(jogador1.coorY,jogador1.coorX);
    
    //ciclo while que corre enquanto a tecla q nao e premida
    while(1)
    {
        mvaddch(jogador1.coorY,jogador1.coorX,'@' | A_BOLD);
        //mvprintw(jogador1.coorY,jogador1.coorX,'@' | A_BOLD);
        refresh();
        mudarstate(&jogador1);
    }
    endwin();
    return 0;
}
