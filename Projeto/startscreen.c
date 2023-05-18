#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>


void startscreen(int MaxX, int MaxY,WINDOW *win){
//ASCII ART
    mvprintw(6 , 8,"                             ,--.	");    mvprintw(4 , MaxX - 56,"                                  ,-.");
    mvprintw(7 , 8,"                            {    }   ");   mvprintw(5 , MaxX - 56,"                                 (\"O_)");
    mvprintw(8 , 8,"                            K,   }   ");   mvprintw(6 , MaxX - 56,"                                / `-/");
    mvprintw(9 , 8,"                           /  `Y`    ");   mvprintw(7 , MaxX - 56,"                               /-. /");
    mvprintw(10 ,8,"                      _   /   /      ");   mvprintw(8 , MaxX - 56,"                              /   )");
    mvprintw(11 ,8,"                     {_'-K.__/       ");   mvprintw(9 , MaxX - 56,"                             /   /");
    mvprintw(12 ,8,"                       `/-.__L._     ");   mvprintw(10 ,MaxX - 56,"                _           /-. /");
    mvprintw(13 ,8,"                       /  ' /`\\_}    ");  mvprintw(11 ,MaxX - 56,"               (_)\"-._     /   )");
    mvprintw(14 ,8,"                      /  ' /         ");   mvprintw(12 ,MaxX - 56,"                 \"-._ \"-'\"\"( )/");
    mvprintw(15, 8,"              ____   /  ' /          ");   mvprintw(13 ,MaxX - 56,"                     \"-/\"-._\" `."); 
    mvprintw(16, 8,"       ,-'~~~~    ~~/  ' /_          ");   mvprintw(14 ,MaxX - 56,"                      /     \"-.'._");
    mvprintw(17, 8,"     ,'             ``~~~%%%%',        "); mvprintw(15 ,MaxX - 56,"                     /\\       /-._\"-._");
    mvprintw(18 ,8,"    (                     %%  Y       ");  mvprintw(16 ,MaxX - 56,"      _,---...__    /  ) _,-\"/    \"-(_)");
    mvprintw(19 ,8,"   {                      %%%% I       "); mvprintw(17, MaxX - 56,"  ___<__(|) _   \"\"-/  / /   /");
    mvprintw(20 ,8,"  {      -                 %%  `.     ");  mvprintw(18 ,MaxX - 56,"   '  `----' \"\"-.   \\/ /   /");
    mvprintw(21 ,8,"  |       ',                %%  )     ");  mvprintw(19 ,MaxX - 56,"                 )  ] /   /");
    mvprintw(22 ,8,"  |        |   ,..__      __. Y      ");   mvprintw(20 ,MaxX - 56,"         ____..-'   //   /                       )");
    mvprintw(23 ,8,"  |    .,_./  Y ' / ^Y   J   )|      ");   mvprintw(21 ,MaxX - 56,"     ,-\"\"      __.,'/   /   ___                 /,");
    mvprintw(24 ,8,"  \\           |' /   |   |   ||      ");  mvprintw(22 ,MaxX - 56,"    /    ,--\"\"/  / /   /,-\"\"   \"\"\"-.          ,'/");
    mvprintw(25 ,8,"   \\          L_/    . _ (_,.'(      ");  mvprintw(23 ,MaxX - 56,"   [    (    /  / /   /  ,.---,_   `._   _,-','");
    mvprintw(26 ,8,"    \\,   ,      ^^""' / |      )     ");  mvprintw(24 ,MaxX - 56,"    \\    `-./  / /   /  /       `-._  \"\"\" ,-'");
    mvprintw(27 ,8,"     \\_  \\          /,L]     /     ");   mvprintw(25 ,MaxX - 56,"     `-._  /  / /   /_,'            \"\"--\"");
    mvprintw(28 ,8,"       '-_`-,       ` `   ./`       ");    mvprintw(26 ,MaxX - 56,"         \"/  / /   /\"         ");
    mvprintw(29 ,8,"          `-(_            )         ");    mvprintw(27 ,MaxX - 56,"         /  / /   /");
    mvprintw(30 ,8,"              ^^\\..___,.--`         ");   mvprintw(28 ,MaxX - 56,"        /  / /   / ");
    mvprintw(31 ,8,"                                      ");  mvprintw(29 ,MaxX - 56,"       /  |,'   /  ");
    mvprintw(32 ,8,"                                      ");  mvprintw(30 ,MaxX - 56,"      :   /    /");
    mvprintw(33 ,8,"                                      ");  mvprintw(31 ,MaxX - 56,"      [  /   ,'");
    mvprintw(34 ,8,"                                      ");  mvprintw(32 ,MaxX - 56,"      | /  ,'");
    mvprintw(35 ,8,"                                      ");  mvprintw(33 ,MaxX - 56,"      |/,-'");
    mvprintw(36 ,8,"                                      ");  mvprintw(34 ,MaxX - 56,"      P'");
    
    
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
