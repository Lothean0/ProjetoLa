#include <ncurses.h>
#include <stdlib.h>
#include "player.h"

typedef struct vetor
{
    int coorY;
    int coorX;
}Vetor;

//func que define um vetor baseado na tecla premida
Vetor calcvetor(void)
{
    //cenas rando
    noecho();

    //define um vetor
    Vetor direcao;
    direcao.coorX=0;
    direcao.coorY=0;

    //input da tecla
    int tecla=getch();

    switch(tecla) {
        case KEY_A1:
		case '7': direcao.coorX = -1; direcao.coorY = -1; break;
        case KEY_UP:
		case '8': direcao.coorX = +0; direcao.coorY = -1; break;
        case KEY_A3:
		case '9': direcao.coorX = +1; direcao.coorY = -1; break;
        case KEY_LEFT:
		case '4': direcao.coorX = -1; direcao.coorY = +0; break;
        case KEY_B2:
		case '5': break;
        case KEY_RIGHT:
		case '6': direcao.coorX = +1; direcao.coorY = +0; break;
        case KEY_C1:
		case '1': direcao.coorX = -1; direcao.coorY = +1; break;
        case KEY_DOWN:
		case '2': direcao.coorX = +0; direcao.coorY = +1; break;
        case KEY_C3:
		case '3': direcao.coorX = +1; direcao.coorY = +1; break;
        case 'q': endwin(),exit(0);
	}
    return direcao; 
}

//func que soma o vetor de ''calcvetor'' à posiçao do player depois de verificar se esta é valida
void mudarstate(Player *jogador)
{
    //retorna a posicao onde o player estava a um espaço pe
    mvaddch(jogador->coorY, jogador->coorX, ' ');

    //começa por pegar um vetor(input da tecla, etc...)
    Vetor direcao = calcvetor();

    //define pTEMP como o "bloco" para onde o player quer ir
    Player pTEMP = {0,0};
    pTEMP.coorX=(jogador->coorX)+(direcao.coorX);
    pTEMP.coorY=(jogador->coorY)+(direcao.coorY);

    //mvinch como o char para onde o player quer ir
    
    switch(mvinch(pTEMP.coorY, pTEMP.coorX)) {
        //casos em que queremos ir para uma parede ou algum local cujo nao podemos ir
        case '#': break; // nestes casos o player nao mexe;
        default: jogador->coorX=pTEMP.coorX; jogador->coorY=pTEMP.coorY; break;//neste caso a posiçao do player passa a ser a do pTEMP
    }
    mvaddch(jogador->coorY, jogador->coorX, '@' | A_BOLD);
}
