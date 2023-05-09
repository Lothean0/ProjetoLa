#ifndef ___STATE_H___
#define ___STATE_H___
typedef struct mapa
{
    char character;
    int distancia;
} Mapa;

int randomgen(void);
void gera_mapa(Mapa **mapa);
int conta_vizinhos(Mapa **matriz, int ys, int xs);
void denoiser(Mapa **matriz, int ys, int xs);
void geracao(Mapa **mapa, int MaxY, int MaxX);

#endif
