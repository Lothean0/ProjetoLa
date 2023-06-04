#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
// #include <SDL2/SDL.h>
#include "typedef.h"
#include "player.h"
#include "menuhud.h"
#include "inimigo.h"
#include "mapa.h"
#define Visivel 1
#define Nao_Visivel 2
#define Visto 3

/*SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;*/
int comparehp(const void *a, const void *b)
{
    Inimigo *inimigoA = (Inimigo *)a;
    Inimigo *inimigoB = (Inimigo *)b;

    return (inimigoB->hp - inimigoA->hp);
}

int main(void)
{
    /*SDL_Init(SDL_INIT_AUDIO); // Inicia o som

    if (SDL_LoadWAV("AHHH.wav", &wavSpec, &wavBuffer, &wavLength) == NULL)
    {
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0)
    {
    }
    while (true)
    {
        int bomba_SOM = getch();

        if (bomba_SOM == 'i')
        {
            SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            SDL_PauseAudioDevice(deviceId, 0);
        }
    }

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();*/

    // cenas do stor
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    // inicializa a window e calcula a "resoluçao do ecra"
    WINDOW *win = initscr();
    inicializar_cor();
    curs_set(0);
    int MaxY, MaxX;
    getmaxyx(win, MaxY, MaxX);
    halfdelay(5);

    // start screen
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');
    startscreen(MaxX, MaxY, win);
    clear();

    // inicializa coisas
    Player jogador1;

jogo: // label para podermos reiniciar o jogo numa eventual morte
    // inicializa o jogador
    jogador1.coorX = 0;
    jogador1.coorY = 0;
    jogador1.hp = 10;
    jogador1.xp = 0;
    jogador1.lv = 0;
    colorir(&jogador1);

    // FLOOR armazena o floor em que o jogador esta
    int FLOOR = 0;
    int maxhp = 10;
    while (jogador1.hp > 0)
    {
        int ciclos = 0;
        MaxX -= 25; // Faz com que o mapa tenha -25 casas que a win (25 casas para o hud )

        // geracao de mapa
        Mapa mapa[MaxY][MaxX];
        gera_mapa(MaxY, MaxX, mapa);
        denoiser(MaxY, MaxX, mapa);
        gerahole(MaxY, MaxX, mapa);

        // coloca o jogador numa posicao random do ecra
        spawn(&jogador1, MaxY, MaxX, mapa);
        mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
        int qinimigo = rand() % 5 + 5;
        Inimigo inimigo[qinimigo];
        for (int i = 0; i < qinimigo; i++)
        {
            inimigo[i].coorY = 0;
            inimigo[i].coorX = 0;
            inimigo[i].cor = Nao_Visivel;
            inimigo[i].hp = abs(FLOOR)*2+10;
            spawnenimigo(&inimigo[i], MaxY, MaxX, mapa);
        }
        int tecla;

        // HUD
        hudbox(MaxX, MaxY);

        // ciclo while que corre enquanto a tecla q nao e premida ou enquanto estamos no mesmo floor
        while (mapa[jogador1.coorY][jogador1.coorX].character != 'X' && jogador1.hp >= 1)
        {
            // da update na distancia dos enimigos
            distancia(MaxY, MaxX, mapa, &jogador1);

            // eliminar inimigos do arrey
            qsort(inimigo, qinimigo, sizeof(Inimigo), comparehp);
            if (inimigo[qinimigo - 1].hp <= 0)
            {
                qinimigo--;
                jogador1.xp += 5;
            }
            if (jogador1.xp >= 20)
            {
                jogador1.lv++;
                jogador1.xp -= 20;
            }
            maxhp = (jogador1.lv * 5) + 10;
            // updates ao jogador
            updatehud(MaxX, MaxY, jogador1, FLOOR, win, qinimigo); // HUD
            colorir(&jogador1);

            if ((tecla = getch()) == 'e') // bomba
            {
                bomba(MaxY, MaxX, mapa, jogador1);
            }
            else if (tecla == 'x') // dont mind me
            {
                jogador1.hp = 0;
            }
            else // ou movimento
            {
                mudarstate(&jogador1, MaxX, tecla, mapa, inimigo, qinimigo);
            }

            // print player
            attron(jogador1.cor);
            mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
            attroff(jogador1.cor);

            // Visao
            FOV(jogador1.coorY, jogador1.coorX, MaxY, MaxX, mapa, inimigo, qinimigo);
            refresh();
            if (ciclos % 3 == 0)
            {
                moveenimigos(inimigo, qinimigo, MaxX, mapa, &jogador1, FLOOR);
            }

            // print inimigo
            for (int i = 0; i < qinimigo; i++)
            {
                attron(COLOR_PAIR(inimigo[i].cor));
                mvaddch(inimigo[i].coorY, inimigo[i].coorX, '%');
                attroff(COLOR_PAIR(inimigo[i].cor));
            }
            bool print = true;
            for (int ys = 0; ys < MaxY; ys++)
            {
                for (int xs = 0; xs < MaxX; xs++)
                {
                    for (int i = 0; i < qinimigo; i++)
                    {
                        if (ys == inimigo[i].coorY && xs == inimigo[i].coorX)
                        {
                            print = false;
                        }
                    }

                    if ((ys != jogador1.coorY || xs != jogador1.coorX) && print)
                    {
                        attron(COLOR_PAIR(mapa[ys][xs].cor)); // Da print em cada character com a sua propria cor
                        mvaddch(ys, xs, mapa[ys][xs].character);
                        attroff(COLOR_PAIR(mapa[ys][xs].cor));
                    }
                    print = true;
                }
            }
            refresh();
            if (ciclos % 10 == 0 && jogador1.hp <= maxhp)
            {
                jogador1.hp++;
                if (jogador1.hp > maxhp)
                {
                    jogador1.hp = maxhp;
                }
            }

            ciclos++;
        }
        clear();
        MaxX += 25;
        FLOOR -= 1;
    }

    // end screen (retry)
    clear();
    int intermitente = 0;
    int quit = 0;
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');
    game_over_screen(MaxY, MaxX, win);
    noecho();
    refresh();
    while ((quit = getch()) != 'q')
    {
        refresh();

        if (intermitente % 2 == 0)
        {
            mvprintw((MaxY / 2) + 10, MaxX / 2 - 8, "PRESS Q TO QUIT");
            mvprintw((MaxY / 2) + 12, MaxX / 2 - 11, "PRESS R TO PLAY AGAIN");
        }
        else
        {
            mvprintw((MaxY / 2) + 10, MaxX / 2 - 9, "                                ");
            mvprintw((MaxY / 2) + 12, MaxX / 2 - 12, "                               ");
        }
        intermitente += 1;
        if (quit == 'r' || quit == 'R')
        {
            goto jogo;
        }
    }

    // termina o jogo (carregar q na endscreen)
    clear();
    endwin();
    return 0;
}
