#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"

// fazer funcao para preecnher o mapa com hastags with probabilidade definida

int preenche_atoa() 
{
    // numero aleatoreo.
    srand(time(NULL));
    int numero_aleatorio = rand() % 100;
}

void gera_mapa(matriz[int x,int y])
{
    int rowinicial = 0; //temporario ns as cenas do hud
    int colinicial = 0; //mm cena

    for (int ys=rowinicial; ys<y; ys++)
    {
        for(int xs=colinicial; xs<x; xs++)
        {
            int chance = randomgen(); //sempre (0<=chance<100)
            if (chance<45)
            {
                matriz[ys,xs].charact = '#'; //45%de chance de os blocos serem # (45/100 blocos sao #)
            } 
            else
            {
                matriz[ys,xs].charact = '.'; //55%  
            }
        }
    }
}










//denoise
int conta_vizinhos()
{
    int vizinhos=0;







    return vizinhos;
}

void espeta_Hastag (int vizinhos, xs, ys)
{
    if(vizinhos == 0) // faz_parede (xs,ys);

    if(vizinhos > 4) // faz_vazio (xs,ys);
    if(vizinhos > 5) // faz_parede (xs,ys);
}
