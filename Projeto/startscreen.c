#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>


void startscreen(int MaxX, int MaxY,WINDOW *win){
//ASCII ART
    mvprintw(6 , 12,"                             ,--.	");    mvprintw(4 , MaxX - 56,"                                  ,-.");
    mvprintw(7 , 12,"                            {    }   ");   mvprintw(5 , MaxX - 56,"                                 (\"O_)");
    mvprintw(8 , 12,"                            K,   }   ");   mvprintw(6 , MaxX - 56,"                                / `-/");
    mvprintw(9 , 12,"                           /  `Y`    ");   mvprintw(7 , MaxX - 56,"                               /-. /");
    mvprintw(10 ,12,"                      _   /   /      ");   mvprintw(8 , MaxX - 56,"                              /   )");
    mvprintw(11 ,12,"                     {_'-K.__/       ");   mvprintw(9 , MaxX - 56,"                             /   /");
    mvprintw(12 ,12,"                       `/-.__L._     ");   mvprintw(10 ,MaxX - 56,"                _           /-. /");
    mvprintw(13 ,12,"                       /  ' /`\\_}    ");  mvprintw(11 ,MaxX - 56,"               (_)\"-._     /   )");
    mvprintw(14 ,12,"                      /  ' /         ");   mvprintw(12 ,MaxX - 56,"                 \"-._ \"-'\"\"( )/");
    mvprintw(15, 12,"              ____   /  ' /          ");   mvprintw(13 ,MaxX - 56,"                     \"-/\"-._\" `."); 
    mvprintw(16, 12,"       ,-'~~~~    ~~/  ' /_          ");   mvprintw(14 ,MaxX - 56,"                      /     \"-.'._");
    mvprintw(17, 12,"     ,'             ``~~~%%%%',        "); mvprintw(15 ,MaxX - 56,"                     /\\       /-._\"-._");
    mvprintw(18 ,12,"    (                     %%  Y       ");  mvprintw(16 ,MaxX - 56,"      _,---...__    /  ) _,-\"/    \"-(_)");
    mvprintw(19 ,12,"   {                      %%%% I       "); mvprintw(17, MaxX - 56,"  ___<__(|) _   \"\"-/  / /   /");
    mvprintw(20 ,12,"  {      -                 %%  `.     ");  mvprintw(18 ,MaxX - 56,"   '  `----' \"\"-.   \\/ /   /");
    mvprintw(21 ,12,"  |       ',                %%  )     ");  mvprintw(19 ,MaxX - 56,"                 )  ] /   /");
    mvprintw(22 ,12,"  |        |   ,..__      __. Y      ");   mvprintw(20 ,MaxX - 56,"         ____..-'   //   /                       )");
    mvprintw(23 ,12,"  |    .,_./  Y ' / ^Y   J   )|      ");   mvprintw(21 ,MaxX - 56,"     ,-\"\"      __.,'/   /   ___                 /,");
    mvprintw(24 ,12,"  \\           |' /   |   |   ||      ");  mvprintw(22 ,MaxX - 56,"    /    ,--\"\"/  / /   /,-\"\"   \"\"\"-.          ,'/");
    mvprintw(25 ,12,"   \\          L_/    . _ (_,.'(      ");  mvprintw(23 ,MaxX - 56,"   [    (    /  / /   /  ,.---,_   `._   _,-','");
    mvprintw(26 ,12,"    \\,   ,      ^^""' / |      )     ");  mvprintw(24 ,MaxX - 56,"    \\    `-./  / /   /  /       `-._  \"\"\" ,-'");
    mvprintw(27 ,12,"     \\_  \\          /,L]     /     ");   mvprintw(25 ,MaxX - 56,"     `-._  /  / /   /_,'            \"\"--\"");
    mvprintw(28 ,12,"       '-_`-,       ` `   ./`       ");    mvprintw(26 ,MaxX - 56,"         \"/  / /   /\"         ");
    mvprintw(29 ,12,"          `-(_            )         ");    mvprintw(27 ,MaxX - 56,"         /  / /   /");
    mvprintw(30 ,12,"              ^^\\..___,.--`         ");   mvprintw(28 ,MaxX - 56,"        /  / /   / ");
    mvprintw(31 ,12,"                                      ");  mvprintw(29 ,MaxX - 56,"       /  |,'   /  ");
    mvprintw(32 ,12,"                                      ");  mvprintw(30 ,MaxX - 56,"      :   /    /");
    mvprintw(33 ,12,"                                      ");  mvprintw(31 ,MaxX - 56,"      [  /   ,'");
    mvprintw(34 ,12,"                                      ");  mvprintw(32 ,MaxX - 56,"      | /  ,'");
    mvprintw(35 ,12,"                                      ");  mvprintw(33 ,MaxX - 56,"      |/,-'");
    mvprintw(36 ,12,"                                      ");  mvprintw(34 ,MaxX - 56,"      P'");
    
    mvprintw((MaxY/2)+15, 15, "A102936 - > André Carvalho");
    mvprintw((MaxY/2)+16, 15, "A100000- > Matias");
    mvprintw((MaxY/2)+17, 15, "A10000 - > Simão");
    mvprintw((MaxY/2)+18, 15, "A10000 - > Pedro");

    mvprintw((MaxY/2)+15, MaxX-30, "Universidade do Minho");
    mvprintw((MaxY/2)+16, MaxX-30, "LCC");
    mvprintw((MaxY/2)+17, MaxX-30, "1º Ano");
    
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
