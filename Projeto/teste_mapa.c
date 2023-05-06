#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"

#define x = 500;
#define y = 500;

//repetido da main mas yau
typedef struct mapa
{
    char character;
    int luz; //??? ns
    int distancia;
}Mapa;

// fazer funcao para preecnher o mapa com hastags with probabilidade definida
int preenche_atoa() 
{
    // numero aleatoreo.
    srand(time(NULL));
    int numero_aleatorio = rand() % 100;
}

void gera_mapa(Mapa mapa[y][x])
{
    int rowinicial = 0; //temporario ns as cenas do hud
    int colinicial = 0; //mm cena

    for (int ys=rowinicial; ys<y; ys++)// dois for's que percorrem o mapa todo coluna a coluna
    {
        for(int xs=colinicial; xs<x; xs++)
        {
            int chance = randomgen(); //sempre (0<=chance<100)
            if (chance<45)
            {
                mapa[ys][xs].character = '#'; //45%de chance de os blocos serem # (45/100 blocos sao #)
            } 
            else
            {
                mapa[ys][xs].character = '.'; //55%  
            }
        }
    }
}

//denoise
int conta_vizinhos(Mapa mapa[y][x], int ys, int xs)
{
    //Contador
    int vizinhos=0;
    
    //verifica quantas das posiçoes à volta da y,x sao #'s 
    if ((matriz[ys+1][xs].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys-1][xs].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys][xs+1].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys][xs-1].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys+1][xs+1].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys-1][xs-1].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys+1][xs-1].character)=='#')
    {
        vizinhos++;
    }
    if ((matriz[ys-1][xs+1].character)=='#')
    {
        vizinhos++;
    }

    return vizinhos;
}

void espeta_Hastag (Mapa mapa[y][x], int ys,int xs,)
{
    int vizinhos = contavizinhos(ys, xs);
    if(vizinhos == 0 || vizinhos >5)// faz_parede (xs,ys);
    {
        matriz[ys, xs].character='#';
    } else
    if(vizinhos > 4) // faz_vazio (xs,ys);
    {
        matriz[ys, xs].character='.';
    } else
    if(vizinhos > 5) // faz_parede (xs,ys);
    {
        matriz[ys, xs].character='#';
    }
}
