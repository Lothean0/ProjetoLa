#ifndef ___STATE_H___
#define ___STATE_H___
typedef struct mapa
{
    char character;
    int distancia;
    int cor;
} Mapa;

int randomgen(int timer);
void gera_mapa(int MaxY, int MaxX,Mapa mapa[][MaxX]);
void denoiser(int MaxY, int MaxX,Mapa mapa[][MaxX]);
void FOV(int player_y, int player_x,int MaxY, int MaxX, Mapa mapa[][MaxX]);
#endif
