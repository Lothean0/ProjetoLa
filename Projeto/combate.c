#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "player.h"
#include "menuhud.h"
#include "inimigo.h"

void attack(Player *player, Inimigo *inimigo1)
{
    //player->hp--;
    inimigo1->hp--;
}