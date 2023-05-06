#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"

// fazer funcao para preecnher o mapa com hastags with probabilidade definida

int preenche_atoa() 
{

    int x = 20;
    int y = 0;

    // numero aleatorio de 40 a 60, para definir a probabilidade de hastags no mapa
    srand(time(NULL));
    int numero_aleatorio = rand() % 20 + 40;

    // preencher na matriz os hastags consoante a probabilidade
    gera_mapa(x,y,numero_aleatorio);
}

void gera_mapa(x,y,random)
{
    int area = x * y;
    int area_ocupada = area * (random/100);

    for (i=0; i<area_ocupada; i++)
    {
        
    }
}











void conta_vizinhos()
{

}

void espeta_Hastag ()
{
    if(vizinhos == 0) faz_parede;
    if(vizinhos > 4) faz_vazio;
    if(vizinhos > 5) faz_parede;
}