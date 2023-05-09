#ifndef ___STATE_H___
#define ___STATE_H___
typedef struct mapa
{
    char character;
    int distancia;
} Mapa;

#define x 1000
#define y 1000

int randomgen(void);
void gera_mapa(Mapa **mapa, int MaxY, int MaxX);
int conta_vizinhos(Mapa **matriz, int ys, int xs, int MaxY, int MaxX);
void denoiser(Mapa **matriz, int ys, int xs, int MaxY, int MaxX);
void geracao(Mapa **mapa, int MaxY, int MaxX);

#endif
