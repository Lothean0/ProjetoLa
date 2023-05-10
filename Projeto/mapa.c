#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "mapa.h"

// #define x 1000
// #define y 1000

// fazer funcao para preecnher o mapa com hastags with probabilidade definida
int randomgen(int timer)
{
    // numero aleatoreo.
    srand(timer);
    int numero_aleatorio = rand() % 100;
    return numero_aleatorio;
}

void gera_mapa(Mapa **mapa, int MaxY, int MaxX)
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
            }
            else
            {
                mapa[i][j].character = '.'; // 55%
                mapa[i][j].distancia = 0;
            }
            seed -= 42;

            if (i == 0 || j == 0 || i == (MaxY - 1) || j == (MaxX - 1) || i == 1 || j == 1)
            {
                mapa[i][j].character = '#';
            }
        }
    }
}

void denoiser(Mapa **mapa, int MaxY, int MaxX)
{
    int maxreps = 7;
    for (int reps = 0; reps < maxreps; reps++)
    {
        for (int ys = 1; ys < MaxY - 1; ys++)
        {
            for (int xs = 1; xs < MaxX - 1; xs++)
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

// funcao que junta tudo
/*void geracao(Mapa **mapa, int MaxY, int MaxX)
{
    gera_mapa(mapa, MaxY, MaxX);
    for (int reps = 0; reps < 1; reps++)
    {
        for (int ys = 0; ys < MaxY; ys++)
        {
            for (int xs = 0; xs < MaxX; xs++)
            {
                denoiser(mapa, ys, xs, MaxY, MaxX);
            }
        }
    }
}*/
