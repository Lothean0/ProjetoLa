#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "typedef.h"

//attack do player
void attack(Inimigo *inimigo1, Player *player)
{
    inimigo1->hp -= (player->lv + 1);
}

//attack do inimigo
void attacki(Player *player, int floor)
{
    player->hp -= abs(floor) + 1;
}