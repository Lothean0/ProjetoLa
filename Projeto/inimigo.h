#ifndef ___INIMIGO___
#define ___INIMIGO___
#include "mapa.h"
typedef struct inimigo
{
    int coorY;
    int coorX;
    int cor;
    int tipo;
    int hp;

} Inimigo;

void spawnenimigo( Inimigo *inimigo, int MaxY, int MaxX);
#endif