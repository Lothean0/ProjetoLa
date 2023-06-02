#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "player.h"

void startscreen(int MaxX, int MaxY, WINDOW *win)
{
    // ASCII ART
    mvprintw(6, 12, "                             ,--.	");
    mvprintw(4, MaxX - 56, "                                  ,-.");
    mvprintw(7, 12, "                            {    }   ");
    mvprintw(5, MaxX - 56, "                                 (\"O_)");
    mvprintw(8, 12, "                            K,   }   ");
    mvprintw(6, MaxX - 56, "                                / `-/");
    mvprintw(9, 12, "                           /  `Y`    ");
    mvprintw(7, MaxX - 56, "                               /-. /");
    mvprintw(10, 12, "                      _   /   /      ");
    mvprintw(8, MaxX - 56, "                              /   )");
    mvprintw(11, 12, "                     {_'-K.__/       ");
    mvprintw(9, MaxX - 56, "                             /   /");
    mvprintw(12, 12, "                       `/-.__L._     ");
    mvprintw(10, MaxX - 56, "                _           /-. /");
    mvprintw(13, 12, "                       /  ' /`\\_}    ");
    mvprintw(11, MaxX - 56, "               (_)\"-._     /   )");
    mvprintw(14, 12, "                      /  ' /         ");
    mvprintw(12, MaxX - 56, "                 \"-._ \"-'\"\"( )/");
    mvprintw(15, 12, "              ____   /  ' /          ");
    mvprintw(13, MaxX - 56, "                     \"-/\"-._\" `.");
    mvprintw(16, 12, "       ,-'~~~~    ~~/  ' /_          ");
    mvprintw(14, MaxX - 56, "                      /     \"-.'._");
    mvprintw(17, 12, "     ,'             ``~~~%%%%',        ");
    mvprintw(15, MaxX - 56, "                     /\\       /-._\"-._");
    mvprintw(18, 12, "    (                     %%  Y       ");
    mvprintw(16, MaxX - 56, "      _,---...__    /  ) _,-\"/    \"-(_)");
    mvprintw(19, 12, "   {                      %%%% I       ");
    mvprintw(17, MaxX - 56, "  ___<__(|) _   \"\"-/  / /   /");
    mvprintw(20, 12, "  {      -                 %%  `.     ");
    mvprintw(18, MaxX - 56, "   '  `----' \"\"-.   \\/ /   /");
    mvprintw(21, 12, "  |       ',                %%  )     ");
    mvprintw(19, MaxX - 56, "                 )  ] /   /");
    mvprintw(22, 12, "  |        |   ,..__      __. Y      ");
    mvprintw(20, MaxX - 56, "         ____..-'   //   /                       )");
    mvprintw(23, 12, "  |    .,_./  Y ' / ^Y   J   )|      ");
    mvprintw(21, MaxX - 56, "     ,-\"\"      __.,'/   /   ___                 /,");
    mvprintw(24, 12, "  \\           |' /   |   |   ||      ");
    mvprintw(22, MaxX - 56, "    /    ,--\"\"/  / /   /,-\"\"   \"\"\"-.          ,'/");
    mvprintw(25, 12, "   \\          L_/    . _ (_,.'(      ");
    mvprintw(23, MaxX - 56, "   [    (    /  / /   /  ,.---,_   `._   _,-','");
    mvprintw(26, 12, "    \\,   ,      ^^"
                     "' / |      )     ");
    mvprintw(24, MaxX - 56, "    \\    `-./  / /   /  /       `-._  \"\"\" ,-'");
    mvprintw(27, 12, "     \\_  \\          /,L]     /     ");
    mvprintw(25, MaxX - 56, "     `-._  /  / /   /_,'            \"\"--\"");
    mvprintw(28, 12, "       '-_`-,       ` `   ./`       ");
    mvprintw(26, MaxX - 56, "         \"/  / /   /\"         ");
    mvprintw(29, 12, "          `-(_            )         ");
    mvprintw(27, MaxX - 56, "         /  / /   /");
    mvprintw(30, 12, "              ^^\\..___,.--`         ");
    mvprintw(28, MaxX - 56, "        /  / /   / ");
    mvprintw(31, 12, "                                      ");
    mvprintw(29, MaxX - 56, "       /  |,'   /  ");
    mvprintw(32, 12, "                                      ");
    mvprintw(30, MaxX - 56, "      :   /    /");
    mvprintw(33, 12, "                                      ");
    mvprintw(31, MaxX - 56, "      [  /   ,'");
    mvprintw(34, 12, "                                      ");
    mvprintw(32, MaxX - 56, "      | /  ,'");
    mvprintw(35, 12, "                                      ");
    mvprintw(33, MaxX - 56, "      |/,-'");
    mvprintw(36, 12, "                                      ");
    mvprintw(34, MaxX - 56, "      P'");

    mvprintw((MaxY / 2) + 15, 15, "A102936 - > Andre Carvalho");
    mvprintw((MaxY / 2) + 16, 15, "A102944- > Matias Goncalves");
    mvprintw((MaxY / 2) + 17, 15, "A102877 - > Simao Martins");
    mvprintw((MaxY / 2) + 18, 15, "A102942 - > Pedro Oliveira");

    mvprintw((MaxY / 2) + 15, MaxX - 30, "Universidade do Minho");
    mvprintw((MaxY / 2) + 16, MaxX - 30, "LCC");
    mvprintw((MaxY / 2) + 17, MaxX - 30, "1º Ano");

    int intermitente = 0;
    while (getch() != ' ')
    {
        noecho();
        box(win, '|', '-');
        if (intermitente % 2 == 0)
        {
            mvprintw((MaxY / 2) + 8, (MaxX / 2) - 12, "PRESS SPACE TO CONTINUE");
        }
        else
        {
            mvprintw((MaxY / 2) + 8, (MaxX / 2) - 12, "                       ");
        }

        intermitente += 1;
        refresh();
    }
}

void hudbox(int MaxX, int MaxY)
{
    // int HudY = 0; // posiçoes do hud (canto sup esquerdo)
    int HudX = MaxX;
    int MaxHudY = MaxY - 1;
    int MaxHudX = HudX + 24;

    mvhline(0, HudX, '_', 24);       // linha de cima
    mvhline(MaxHudY, HudX, '_', 24); // linha de baixo
    mvvline(0, HudX, '|', MaxY);     // linha da esquerda
    mvvline(0, MaxHudX, '|', MaxY);  // linha da direita
}

// Updates do hud #####
// Posiçao base da box do hud é (HudY, HudX) Posiçao Max (MaxHudY, MaxHudX)

void updatehud(int MaxX, int MaxY, Player jogador1, int FLOOR, WINDOW *win)
{
    // int HudY = 0; // posiçoes do hud (canto sup esquerdo)
    int HudX = MaxX + 1;
    int MaxHudY = MaxY - 1;
    int MaxHudX = HudX + 23;
    int MidHudX = MaxHudX - 12; // meio do hud, ajuda a centrar

    // na coordenadaX por norma tiramos metade na length da string

    // INFO JOGADOR
    mvwprintw(win, 3, MidHudX - 4, "JOGADOR 1");
    mvwprintw(win, 5, MidHudX - 7, "POS : ( %d , %d ) ", jogador1.coorX, jogador1.coorY);
    mvwprintw(win, 7, MidHudX - 4, "HP : ( %d ) ", jogador1.hp);
    mvwprintw(win, 25, MidHudX - 5, "FLOOR ( %d )  ", FLOOR);

    // COMANDOS / CONTROLOS
    mvhline(MaxHudY - 15, HudX, '-', 23);
    mvwprintw(win, MaxHudY - 14, MidHudX - 4, "COMMANDS");
    mvhline(MaxHudY - 13, HudX, '-', 23);

    mvwprintw(win, MaxHudY - 9, MidHudX - 3, "MOVEMENT");
    mvwprintw(win, MaxHudY - 8, MidHudX - 2, "7 8 9");
    mvwprintw(win, MaxHudY - 7, MidHudX - 2, "4   6");
    mvwprintw(win, MaxHudY - 6, MidHudX - 2, "1 2 3");
    mvwprintw(win, MaxHudY - 4, MidHudX - 4, "BOMBS - E");
    mvwprintw(win, MaxHudY - 2, MidHudX - 4, "QUIT - Q");

    wrefresh(win);
}
