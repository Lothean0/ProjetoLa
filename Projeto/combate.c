#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "typedef.h"

void attack(Inimigo *inimigo1, Player *player)
{

    inimigo1->hp -= (player->lv + 1);
}

void attacki(Player *player, int floor)
{
    player->hp -= abs(floor) + 1;
    // inimigo1->hp--;
}