#include <ncurses.h>
#include <stdlib.h>
#include "typedef.h"
#include "combate.h"

typedef struct vetor
{
    int coorY;
    int coorX;
} Vetor;

// func que define um vetor baseado na tecla premida
Vetor calcvetor(int tecla)
{
    // nao imprimir na tela o input
    // ativar o keypad para podermos tambem usar as setas
    noecho();
    keypad(stdscr, true);

    // define um vetor
    Vetor direcao;
    direcao.coorX = 0;
    direcao.coorY = 0;

    // input da tecla

    switch (tecla)
    {
    case KEY_A1:
    case '7':
        direcao.coorX = -1;
        direcao.coorY = -1;
        break;
    case KEY_UP:
    case '8':
        direcao.coorX = +0;
        direcao.coorY = -1;
        break;
    case KEY_A3:
    case '9':
        direcao.coorX = +1;
        direcao.coorY = -1;
        break;
    case KEY_LEFT:
    case '4':
        direcao.coorX = -1;
        direcao.coorY = +0;
        break;
    case KEY_B2:
    case '5':
        break;
    case KEY_RIGHT:
    case '6':
        direcao.coorX = +1;
        direcao.coorY = +0;
        break;
    case KEY_C1:
    case '1':
        direcao.coorX = -1;
        direcao.coorY = +1;
        break;
    case KEY_DOWN:
    case '2':
        direcao.coorX = +0;
        direcao.coorY = +1;
        break;
    case KEY_C3:
    case '3':
        direcao.coorX = +1;
        direcao.coorY = +1;
        break;
    case 'q':
        endwin(), exit(0);
    }
    return direcao;
}

void moveenimigos(Inimigo inimigo[], int qinimigo, int MaxX, Mapa mapa[][MaxX], Player *jogador, int floor)
{
    for (int i = 0; i < qinimigo; i++) // ciclo q passa por todos os inimigos vivos
    {
        Vetor pontoprox; // define um vetor temporario como a posiçao inicial
        pontoprox.coorY = inimigo[i].coorY;
        pontoprox.coorX = inimigo[i].coorX;
        for (int x = inimigo[i].coorX - 1; x <= inimigo[i].coorX + 1; x++)
        {
            for (int y = inimigo[i].coorY - 1; y <= inimigo[i].coorY + 1; y++)
            {
                char chartemp = mapa[y][x].character;

                if (chartemp != '#' && chartemp != 'X')
                {
                    if (mapa[y][x].distancia <= mapa[pontoprox.coorY][pontoprox.coorX].distancia)
                    {
                        pontoprox.coorY = y;
                        pontoprox.coorX = x;
                    }
                }
            }
        }

        if (pontoprox.coorY == jogador->coorY && pontoprox.coorX == jogador->coorX)
        {
            attacki(jogador, floor);
        }
        else
        {
            // muda a pos de cada inimigo para a mais proxima das 9 posiçoes
            inimigo[i].coorY = pontoprox.coorY;
            inimigo[i].coorX = pontoprox.coorX;
        }
    }
}

// func que soma o vetor de ''calcvetor'' à posiçao do player depois de verificar se esta é valida
void mudarstate(Player *jogador, int MaxX, int tecla, Mapa mapa[][MaxX], Inimigo inimigo[], int maxinimigos)
{
    int move;
    // começa por pegar um vetor(input da tecla, etc...)
    Vetor direcao = calcvetor(tecla);

    // define pTEMP como o "bloco" para onde o player quer ir
    Player pTEMP = {0, 0, 0, 0, 0, 0};
    pTEMP.coorX = (jogador->coorX) + (direcao.coorX);
    pTEMP.coorY = (jogador->coorY) + (direcao.coorY);

    // mvinch como o char para onde o player quer ir. Isto e a condiçao para verificar e o movimento e possivel ou nao
    // mvinch nao funciona com cor, logo usamos .character na matriz mapa

    switch (mapa[pTEMP.coorY][pTEMP.coorX].character)
    {
    case '.':
        move = 0;
        for (int i = 0; i < maxinimigos; i++)
        {
            if (inimigo[i].coorY == pTEMP.coorY && inimigo[i].coorX == pTEMP.coorX)
            {
                move = 1;
                attack(&inimigo[i], jogador);
            }
        }
        if (move == 0)
        {
            jogador->coorX = pTEMP.coorX;
            jogador->coorY = pTEMP.coorY;
        }
        break;
    case 'X':
        // Fazer uma trail dos movimentos do jogador, ou seja, adicionar um . as posiçoes previas
        jogador->coorX = pTEMP.coorX;
        jogador->coorY = pTEMP.coorY;
        break; // neste caso a posiçao do player passa a ser a do pTEMP
    // casos em que queremos ir para uma parede ou algum local cujo nao podemos ir // nestes casos o player nao mexe;
    default:
        break;
    }
}

//coloca '.' no arrey do mapa num 3x3 á volta do player
void bomba(int MaxY, int MaxX, Mapa mapa[][MaxX], Player jogador1)
{
    int Xtemp = jogador1.coorX, Ytemp = jogador1.coorY;
    for (int ys = Ytemp - 1; ys <= Ytemp + 1; ys++)
    {
        for (int xs = Xtemp - 1; xs <= Xtemp + 1; xs++)
        {
            if (ys > 0 && xs > 0 && ys < MaxY - 1 && xs < MaxX - 1 && mapa[ys][xs].character != 'X')
            {
                mapa[ys][xs].character = '.';
            }
        }
    }
}
