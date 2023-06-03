#ifndef ___PLAYER___
#define ___PLAYER___
typedef struct player
{
    int coorY;
    int coorX;
    int cor;
    int hp;

} Player;
#endif

#ifndef ___MAPA___
#define ___MAPA___
typedef struct mapa
{
    char character;
    int distancia;
    int cor;
} Mapa;
#endif

#ifndef ___INIMIGO___
#define ___INIMIGO___
typedef struct inimigo
{
    int coorY;
    int coorX;
    int cor;
    int tipo;
    int hp;

} Inimigo;
#endif