#ifndef ___PLAYER___
#define ___PLAYER___
#include "mapa.h"

typedef struct player
{
    int coorY;
    int coorX;
    int cor;

} Player;

void spawn(Player *jogador, int MaxY, int MaxX);
void mudarstate(Player *jogador,int MaxX, int tecla, Mapa mapa[][MaxX]);
void colorir(Player *jogador);
void inicializar_cor(void);
void bomba(int MaxY, int MaxX, Mapa mapa[][MaxX], Player jogador1, int HudX, WINDOW *win);

#endif
