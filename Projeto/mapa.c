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

// fazer funcao para preecnher o mapa com hastags with probabilidade definida
int randomgen(int seed)
{
    // numero aleatoreo.
    srand(seed);
    int numero_aleatorio = rand() % 100;
    return numero_aleatorio;
}

void spawn(Player *jogador, int MaxY, int MaxX)
{
    while (mvinch(jogador->coorY, jogador->coorX) == '#')
    {
        srand(time(NULL));
        jogador->coorY = rand() % MaxY;
        jogador->coorX = rand() % MaxX;
    }
}


void gera_mapa(int MaxY, int MaxX, Mapa mapa[][MaxX])
{
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
                mapa[i][j].cor = 2;
            }
            else
            {
                mapa[i][j].character = '.'; // 55%
                mapa[i][j].distancia = 0;
                mapa[i][j].cor = 2;
            }
            seed -= 42;

            if (i == 0 || j == 0 || i == (MaxY - 1) || j == (MaxX - 1) || i == 1 || j == 1)
            {
                mapa[i][j].character = '#';
            }
        }
    }
}

void denoiser(int MaxY, int MaxX, Mapa mapa[][MaxX])
{
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
}

void gerahole(int MaxY, int MaxX, Mapa mapa[][MaxX])
{
    int posx = 0;
    int posy = 0;
    while (mapa[posy][posx].character == '#')
    {
        srand(time(NULL));
        posx = rand() % MaxX;
        posy = rand() % MaxY;
    }
    for (int i = (posy - 1); i <= (posy + 1); i++)
    {
        for (int l = (posx - 1); l <= (posx + 1); l++)
        {
            mapa[i][l].character = 'X';
            mapa[i][l].cor = 1;
            mapa[i][l].distancia = 0;
        }
    }
}

void imprime(int MaxY, int MaxX, Mapa mapa[][MaxX], WINDOW *win)
{
     for (int ys = 0; ys < MaxY; ys++)
        {
            for (int xs = 0; xs < MaxX; xs++)
            {
                mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
            }
        }
}
