#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "mapa.h"

//#define x 1000
//#define y 1000

// fazer funcao para preecnher o mapa com hastags with probabilidade definida
int randomgen(void)
{
    // numero aleatoreo.
    srand(time(NULL));
    int numero_aleatorio = rand() % 100;
    return numero_aleatorio;
}

void gera_mapa(Mapa **mapa, int MaxY, int MaxX)
{
    int rowinicial = 0; // temporario ns as cenas do hud
    int colinicial = 0; // mm cena

    //ns
    //int y=MaxY;
    //int x=MaxX;

    for (int ys = rowinicial; ys < MaxY; ys++) // dois for's que percorrem o mapa todo coluna a coluna
    {
        for (int xs = colinicial; xs < MaxX; xs++)
        {
            int chance = randomgen(); // sempre (0<=chance<100)
            if (chance < 45)
            {
                mapa[ys][xs].character = ' '; // 45%de chance de os blocos serem # (45/100 blocos sao #)
            }
            else
            {
                mapa[ys][xs].character = ' '; // 55%
            }
        }
    }
}

// denoise
int conta_vizinhos(Mapa **matriz, int ys, int xs, int MaxY, int MaxX)
{
    // Contador
    int vizinhos = 0;

    if (ys > 1 && ys < (MaxY - 1) && xs > 1 && xs < (MaxX - 1))
    {
        // verifica quantas das posiçoes à volta da y,x sao #'s
        if ((matriz[ys + 1][xs].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys - 1][xs].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys][xs + 1].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys][xs - 1].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys + 1][xs + 1].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys - 1][xs - 1].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys + 1][xs - 1].character) == '#')
        {
            vizinhos++;
        }
        if ((matriz[ys - 1][xs + 1].character) == '#')
        {
            vizinhos++;
        }
    }
    return vizinhos;
}

void denoiser(Mapa **matriz, int ys, int xs, int MaxY, int MaxX)
{
    int vizinhos = conta_vizinhos(matriz, ys, xs, MaxY, MaxX);
    if (vizinhos == 0 || vizinhos > 5) // faz_parede (xs,ys);
    {
        matriz[ys][xs].character = '#';
    }
    else if (vizinhos > 4) // faz_vazio (xs,ys);
    {
        matriz[ys][xs].character = '.';
    }
    else if (vizinhos > 5) // faz_parede (xs,ys);
    {
        matriz[ys][xs].character = '#';
    }
}

// funcao que junta tudo
void geracao(Mapa **mapa, int MaxY, int MaxX)
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
}
