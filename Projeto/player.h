#ifndef ___PLAYER2___
#define ___PLAYER2___
#include "typedef.h"


void spawn(Player *jogador, int MaxY, int MaxX, Mapa mapa[][MaxX]);
void mudarstate(Player *jogador, int MaxX, int tecla, Mapa mapa[][MaxX], Inimigo inimigo[], int maxinimigos);
void colorir(Player *jogador);
void inicializar_cor(void);
void bomba(int MaxY, int MaxX, Mapa mapa[][MaxX], Player jogador1, int HudX);

#endif
