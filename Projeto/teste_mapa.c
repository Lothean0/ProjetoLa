#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"

// fazer funcao para preecnher o mapa com hastags with probabilidade definida

int preenche_atoa() 
{
    int numero_aleatorio = rand() % 20 + 40;
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