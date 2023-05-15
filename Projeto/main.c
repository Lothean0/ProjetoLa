#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "mapa.h"
#define Visivel 1
#define Nao_Visivel 2
#define Visto 3

void spawn(Player *jogador, int MaxY, int MaxX)
{
    while (mvinch(jogador->coorY, jogador->coorX) == '#')
    {
        srand(time(NULL));
        jogador->coorY = rand() % MaxY;
        jogador->coorX = rand() % MaxX;
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
    halfdelay(5);

    // HUD
    MaxX -= 25; // Faz com que o mapa tenha -20 casas que a win (20 casas para o hud )

    int HudY = 0; // posiçoes do hud (canto sup esquerdo)
    int HudX = MaxX;
    int MaxHudY = MaxY - 1;
    int MaxHudX = HudX + 24;

    mvhline(0, HudX, '#', 24);        // linha de cima
    mvhline(MaxY - 1, HudX, '#', 24); // linha de baixo
    mvvline(0, HudX, '#', MaxY);      // linha da esquerda
    mvvline(0, MaxHudX, '#', MaxY);   // linha da direita
            
    // gerar mapa?
    Mapa mapa[MaxY][MaxX];

    // gera_mapa(mapa,MaxY,MaxX);
    int i, j, seed;
    seed = (time(NULL));
    for (i = 0; i < MaxY; i++)
    {
        for (j = 0; j < MaxX; j++)
        {
            int chance = randomgen(seed); // sempre (0<=chance<100)
            if (chance < 46)
            {
                mapa[i][j].character = '#';
                mapa[i][j].distancia = 0;
                mapa[i][j].cor = COLOR_PAIR(Nao_Visivel);
                mapa[i][j].visao = 0;
            }
            else
            {
                mapa[i][j].character = '.'; // 55%
                mapa[i][j].distancia = 0;
                mapa[i][j].cor = COLOR_PAIR(Nao_Visivel);
                mapa[i][j].visao = 0;
            }
            seed -= 42;

            if (i == 0 || j == 0 || i == (MaxY - 1) || j == (MaxX - 1) || i == 1 || j == 1)
            {
                mapa[i][j].character = '#';
            }
        }
    }
    // denoiser(mapa,MaxY,MaxX);
    //  DENOISER
    int maxreps = 7;
    for (int reps = 0; reps < maxreps; reps++)
    {
        for (int ys = 2; ys < MaxY - 1; ys++)
        {
            for (int xs = 2; xs < MaxX - 1; xs++)
            {
                // Contador
                int vizinhos = 0;

                if ((ys > 1 && ys < (MaxY - 1)) && (xs > 1 && xs < (MaxX - 1)))
                {
                    // verifica quantas das posiçoes à volta da y,x sao #'s
                    if ((mapa[ys + 1][xs].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys - 1][xs].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys][xs + 1].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys][xs - 1].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys + 1][xs + 1].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys - 1][xs - 1].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys + 1][xs - 1].character) == '#')
                    {
                        vizinhos++;
                    }
                    if ((mapa[ys - 1][xs + 1].character) == '#')
                    {
                        vizinhos++;
                    }
                }

                // TIPO MINESWEEPER
                if (vizinhos == 0 || vizinhos > 4) // faz_parede (xs,ys);
                {
                    mapa[ys][xs].character = '#';
                }
                else if (vizinhos < 4) // faz_vazio (xs,ys);
                {
                    mapa[ys][xs].character = '.';
                }

                // Na ultima repetiçao esta parte limpa os #'s inuteis no meio do mapa
                if (reps == maxreps - 1)
                {
                    if (vizinhos == 0) // faz_parede (xs,ys);
                    {
                        mapa[ys][xs].character = '.';
                    }
                    else if (vizinhos == 8)
                    {
                        mapa[ys][xs].character = '#';
                    }
                }
            }
        }
    }

    // PRINT
    for (int ys = 0; ys < MaxY; ys++)
    {
        for (int xs = 0; xs < MaxX; xs++)
        {
            mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
        }
    }

    // coloca o jogador numa posicao random do ecra
    spawn(&jogador1, MaxY, MaxX);
    mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);

    for (int ys = 0; ys < MaxY; ys++)
    {
        for (int xs = 0; xs < MaxX; xs++)
        {
            // attron(COLOR_PAIR(Nao_Visivel));
            mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
            // attroff(COLOR_PAIR(Nao_Visivel));
        }
    }
    // int timer = 0; //inicia o timer
    int tecla;
    // ciclo while que corre enquanto a tecla q nao e premida
    while (1)
    {
        // Timer
        // move(2, 2);
        //  printw("(%d)", timer);
        // timer++;

        // updates ao jogador
        colorir(&jogador1);
        if ((tecla = getch()) == 'e')
        {
            int Xtemp = jogador1.coorX, Ytemp = jogador1.coorY, timerB = 0;

            mapa[Ytemp][Xtemp].character = '0';
            refresh();
            
            while(timerB<=3)
            {

            //timer da explosão
            timerB++;

            // Explosão
            if(timerB >= 3){
                for (int ys = Ytemp - 2; ys <= Ytemp + 2; ys++)
                {
                    for (int xs = Xtemp - 2; xs <= Xtemp + 2; xs++)
                    {
                        mapa[ys][xs].character='.';
                    }
                }
            }
            
            }
        }
        else
        {
            mudarstate(&jogador1, tecla);
        }
        move(jogador1.coorY, jogador1.coorX);
        attron(jogador1.cor);
        mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
        attroff(jogador1.cor);
        refresh();



        // Updates do hud #####
        // Posiçao base da box do hud é (HudY, HudX) Posiçao Max (MaxHudY, MaxHudX)

        mvprintw(4, HudX + 7, "JOGADOR 1");
        mvprintw(7, HudX + 4, "POS : ( %d , %d )", jogador1.coorX, jogador1.coorY);

        // colorirm(mapa[jogador1.coorY][jogador1.coorX]);
        {
            for (int ys = 0; ys < MaxY; ys++)
            {
                for (int xs = 0; xs < MaxX; xs++)
                {
                    if (ys == jogador1.coorY && xs == jogador1.coorX)
                    {
                    }
                    else
                    {
                        // attron(mapa[ys][xs].cor);
                        mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
                        // attroff(mapa[ys][xs].cor);
                    }
                }
            }
        }
        refresh();
    }
    endwin();
    return 0;
}
