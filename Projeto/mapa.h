#ifndef ___STATE_H___
#define ___STATE_H___
typedef struct mapa
{
    char character;
    int distancia;
} Mapa;

int randomgen(int timer);
void gera_mapa(Mapa **mapa, int MaxY, int MaxX);
void denoiser(Mapa **mapa, int MaxY, int MaxX);
#endif
