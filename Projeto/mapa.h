#ifndef ___STATE_H___
#define ___STATE_H___
typedef struct mapa
{
    char character;
    //int luz; //??? ns
    //int distancia;
} Mapa;

int randomgen(void);
void gera_mapa(Mapa **mapa, int MaxY, int MaxX);
int conta_vizinhos(Mapa **matriz, int ys, int xs, int MaxY, int MaxX);
void denoiser(Mapa **matriz, int ys, int xs, int MaxY, int MaxX);
void geracao(Mapa **mapa, int MaxY, int MaxX);

#endif
