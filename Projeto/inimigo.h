#ifndef ___INIMIGO2___
#define ___INIMIGO2___
#include "typedef.h"

void spawnenimigo(Inimigo *inimigo, int MaxY, int MaxX, Mapa mapa[][MaxX]);
void moveenimigos(Inimigo *inimigo, int qinimigo, int Maxy, int MaxX, Mapa mapa[][MaxX]);
#endif
