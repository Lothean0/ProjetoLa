#ifndef ___HUD___
#define ___HUD___
#include "typedef.h"
void startscreen(int MaxX, int MaxY, WINDOW *win);
void hudbox(int MaxX,int MaxY);
void updatehud(int MaxX, int MaxY, Player jogador1, int FLOOR, WINDOW *win);
void game_over_screen(int MaxY, int MaxX, WINDOW *win);
#endif
