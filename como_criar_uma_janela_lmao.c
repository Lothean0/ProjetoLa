#include <stdio.h>
#include <ncurses.h>

/* 
    ATENCAO as coordenadas no ncurses é assim (Y,X)
    movwprint(janela,condicoes)  -> W significa window
    wget()
    wattroff(janela, A_REVERSE) -> atribui propiedades ex: cores, neste caso ele reverte as cores
    newwin(tamanho Y, tamanho X, begY, begX)
    box(janela, 0,0)
    >>>>>>>><<<<<<<<<
    Funcao getch();    
    keypad(janela,True)
*/


int criawindow ()
{
    cbreak();
    noecho(); // remove os inputs

    int xmax, ymax, xmin, ymin;
    int i, escolha;
    char opcoes[4][10]= {"opcao 1", "opcao 2", "opcao 3", "opcao 4"};
    int destacar;
    getmaxyx(stdscr, ymax, xmax);  // funcao que pega nos valores maximos de cada variavel no plano



    WINDOW * menu = newwin(10, (xmax -7), (ymax -44), 4);
    box(menu,0,0);
    refresh();
}

// nodelay() //mesmo q nao carregarmos numa tecla o ciclo vai continuar (ou seja o jogo vai continuar mesmo sem premir teclas)