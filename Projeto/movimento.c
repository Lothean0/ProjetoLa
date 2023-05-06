#include <ncurses.h>
#include "player.h"

typedef struct vetor
{
    int coorY;
    int coorX;

}Vetor;

//func que define um vetor baseado na tecla premida
Vetor calcvetor(void)
{
    //define um vetor
    Vetor direcao;
    direcao.coorX=0;
    direcao.coorY=0;

    //input da tecla
    char tecla=getch();

    switch(tecla) {
		//case KEY_A1:
		case '7': direcao.coorX = -1; direcao.coorY = -1; break;
		//case KEY_UP:
		case '8': direcao.coorX = +0; direcao.coorY = -1; break;
		//case KEY_A3:
		case '9': direcao.coorX = +1; direcao.coorY = -1; break;
		//case KEY_LEFT:
		case '4': direcao.coorX = -1; direcao.coorY = +0; break;
		//case KEY_B2:
		case '5': break;
		//case KEY_RIGHT:
		case '6': direcao.coorX = +1; direcao.coorY = +0; break;
		//case KEY_C1:
		case '1': direcao.coorX = -1; direcao.coorY = +1; break;
		//case KEY_DOWN:
		case '2': direcao.coorX = +0; direcao.coorY = +1; break;
		//case KEY_C3:
		case '3': direcao.coorX = +1; direcao.coorY = +1; break;
		case 'q': endwin(); exit(0); break;
	}
    return direcao; 
}

//func que soma o vetor de ''calcvetor'' à posiçao do player depois de verificar se esta é valida
void mudarstate(Player *jogador)
{
    //começa por pegar um vetor(input da tecla, etc...)
    Vetor direcao = calcvetor();

    //define pTEMP como o "bloco" para onde o player quer ir
    Player pTEMP = {0,0};
    pTEMP.coorX=(jogador->coorX)+(direcao.coorX);
    pTEMP.coorY=(jogador->coorY)+(direcao.coorY);

    //define c como o char para onde o player quer ir
    //char c = mvinch(pTEMP.coorY, pTEMP.coorX);
    char c = mvinch((jogador->coorY)+(direcao.coorY),(jogador->coorX)+(direcao.coorX));

    mvaddch(jogador->coorY, jogador->coorX, ' ');
    
    switch(c) {
        //casos em que queremos ir para uma parede ou algum local cujo nao podemos ir
        //case '└':
        //case '┘':
        //case '┌':
        //case '┐':
        case '|':
        case '-': break; // nestes casos o player nao mexe;
        case '*': jogador->coorX=pTEMP.coorX; jogador->coorY=pTEMP.coorY; break;//neste caso a posiçao do player passa a ser a do pTEMP
    }

}
