#ifndef ___PLAYER___
#define ___PLAYER___

typedef struct player
{
    int coorY;
    int coorX;
    int cor;

} Player;

void spawn(Player *jogador, int MaxY, int MaxX);
void mudarstate(Player *jogador);
void colorir(Player *jogador);
void inicializar_cor();

#endif
