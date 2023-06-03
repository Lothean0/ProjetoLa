#ifndef ___STATE_H___
#define ___STATE_H___

#include "typedef.h"

int randomgen(int seed);
void gera_mapa(int MaxY, int MaxX,Mapa mapa[][MaxX]);
void denoiser(int MaxY, int MaxX,Mapa mapa[][MaxX]);
void FOV(int player_y, int player_x,int MaxY, int MaxX, Mapa mapa[][MaxX], Inimigo inimigo[],int qinimigos);
void gerahole(int MaxY, int MaxX,Mapa mapa[][MaxX]);
void imprime(int MaxY, int MaxX, Mapa mapa[][MaxX], WINDOW *win);
void distancia(int MaxY, int MaxX, Mapa mapa[][MaxX], Player *jogador);
#endif
