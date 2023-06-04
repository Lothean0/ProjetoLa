#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "typedef.h"

void attack(Inimigo *inimigo1)
{
    //player->hp--;
    inimigo1->hp--;
}

void attacki(Player *player)
{
    player->hp--;
    //inimigo1->hp--;
}