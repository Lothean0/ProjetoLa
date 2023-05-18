#include <ncurses.h>
#include <stdlib.h>
#include "player.h"
#include "mapa.h"

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

// func que soma o vetor de ''calcvetor'' à posiçao do player depois de verificar se esta é valida
void mudarstate(Player *jogador, int MaxX, int tecla, Mapa mapa[][MaxX])
{
    // começa por pegar um vetor(input da tecla, etc...)
    Vetor direcao = calcvetor(tecla);

    // define pTEMP como o "bloco" para onde o player quer ir
    Player pTEMP = {0, 0, 0};
    pTEMP.coorX = (jogador->coorX) + (direcao.coorX);
    pTEMP.coorY = (jogador->coorY) + (direcao.coorY);

    // mvinch como o char para onde o player quer ir. Isto e a condiçao para verificar e o movimento e possivel ou nao
    // mvinch nao funciona com cor, logo usamos .character na matriz mapa
    switch (mapa[pTEMP.coorY][pTEMP.coorX].character)
    {
    // casos em que queremos ir para uma parede ou algum local cujo nao podemos ir
    case '#':
        break; // nestes casos o player nao mexe;
    default:
        // Fazer uma trail dos movimentos do jogador, ou seja, adicionar um . as posiçoes previas
        jogador->coorX = pTEMP.coorX;
        jogador->coorY = pTEMP.coorY;
        break; // neste caso a posiçao do player passa a ser a do pTEMP
    }
    mvaddch(jogador->coorY, jogador->coorX, '@' | A_BOLD);
}
void bomba(int MaxY, int MaxX, Mapa mapa[][MaxX], Player jogador1, int HudX)
{
    int Xtemp = jogador1.coorX, Ytemp = jogador1.coorY, timerB = 0;

    mapa[Ytemp][Xtemp].character = '0';
    refresh();

    // timer da explosão
    while (timerB < 5)
    {
        timerB++;
        mvprintw(8, HudX + 7, "timerB=%d", timerB);

        // Explosão
        if (timerB == 5)
        {
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
    }
}
