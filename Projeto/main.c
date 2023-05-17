#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "player.h"
#include "mapa.h"
// biblioteca do som
#include <SDL2/SDL.h>

#define Visivel 1
#define Nao_Visivel 2
#define Visto 3

SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;

SDL_Init(SDL_INIT_AUDIO);  // Inicia o som

if (SDL_LoadWAV("AHHH.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {}

SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
if (deviceId == 0) {}
while (true) 
{
    int bomba_SOM = getch();

    if (bomba_SOM == 'q') {
        SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);
    }
}

SDL_CloseAudioDevice(deviceId);  
SDL_FreeWAV(wavBuffer);
SDL_Quit();

void spawn(Player *jogador, int MaxY, int MaxX)
{
    while (mvinch(jogador->coorY, jogador->coorX) == '#')
    {
        srand(time(NULL));
        jogador->coorY = rand() % MaxY;
        jogador->coorX = rand() % MaxX;
    }
}

int main(void)
{
    // inicializa o jogador
    Player jogador1;
    jogador1.coorX = 0;
    jogador1.coorY = 0;

    // cenas do stor
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    // inicializa a window e calcula a "resoluçao do ecra"
    WINDOW *win = initscr();
    inicializar_cor();
    colorir(&jogador1);
    curs_set(0);
    int MaxY, MaxX;
    getmaxyx(win, MaxY, MaxX);
    halfdelay(5);

    // start screen
    int intermitente = 0;
    while (getch() != ' ')
    {
        noecho();
        box(win, '|', '-');
        // ascii art

        if (intermitente % 2 == 0)
        {
            mvprintw((MaxY / 2) + 8, (MaxX / 2) - 12, "PRESS SPACE TO CONTINUE");
        }
        else
        {
            mvprintw((MaxY / 2) + 8, (MaxX / 2) - 12, "                       ");
        }
        refresh();
    }

    clear();

    // HUD
    MaxX -= 25; // Faz com que o mapa tenha -20 casas que a win (20 casas para o hud )
    // int HudY = 0; // posiçoes do hud (canto sup esquerdo)
    int HudX = MaxX;
    // int MaxHudY = MaxY - 1;
    int MaxHudX = HudX + 24;

    mvhline(0, HudX, '_', 24);        // linha de cima
    mvhline(MaxY - 1, HudX, '_', 24); // linha de baixo
    mvvline(0, HudX, '|', MaxY);      // linha da esquerda
    mvvline(0, MaxHudX, '|', MaxY);   // linha da direita

    // geracao de mapa
    Mapa mapa[MaxY][MaxX];

    gera_mapa(MaxY, MaxX, mapa);
    denoiser(MaxY, MaxX, mapa);

    // PRINT
    for (int ys = 0; ys < MaxY; ys++)
    {
        for (int xs = 0; xs < MaxX; xs++)
        {
            mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
        }
    }

    // coloca o jogador numa posicao random do ecra
    spawn(&jogador1, MaxY, MaxX);
    mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);

    for (int ys = 0; ys < MaxY; ys++)
    {
        for (int xs = 0; xs < MaxX; xs++)
        {
            attron(COLOR_PAIR(Nao_Visivel));
            mvwprintw(win, ys, xs, "%c", mapa[ys][xs].character);
            attroff(COLOR_PAIR(Nao_Visivel));
        }
    }
    // int timer = 0; //inicia o timer
    int tecla;
    // ciclo while que corre enquanto a tecla q nao e premida
    while (1)
    {

        // Timer
        // move(2, 2);
        //  printw("(%d)", timer);
        // timer++;

        // updates ao jogador
        colorir(&jogador1);

        // bomba
        if ((tecla = getch()) == 'e')
        {
            int Xtemp = jogador1.coorX, Ytemp = jogador1.coorY, timerB = 0;

            mapa[Ytemp][Xtemp].character = '0';
            refresh();

            // timer da explosão
            while (timerB < 5)
            {
                timerB++;
                mvprintw(8, HudX + 7, "timerB=%d", timerB);

                // Explosão
                if (timerB == 5)
                {
                    for (int ys = Ytemp - 1; ys <= Ytemp + 1; ys++)
                    {
                        for (int xs = Xtemp - 1; xs <= Xtemp + 1; xs++)
                        {
                            if (ys > 0 && xs > 0 && ys < MaxY-1 && xs < MaxX-1)
                            {
                                mapa[ys][xs].character = '.';
                            }
                            //else
                            //{
                            //    mapa[ys][xs].character = '.';
                            //}
                        }
                    }
                }
            }
        }
        else
        {
            mudarstate(&jogador1, MaxX, tecla, mapa);
        }
        move(jogador1.coorY, jogador1.coorX);
        attron(jogador1.cor);
        mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
        attroff(jogador1.cor);
        FOV(jogador1.coorY, jogador1.coorX, MaxY, MaxX, mapa);
        refresh();

        // Updates do hud #####
        // Posiçao base da box do hud é (HudY, HudX) Posiçao Max (MaxHudY, MaxHudX)

        mvprintw(4, HudX + 7, "JOGADOR 1");
        mvprintw(7, HudX + 4, "POS : ( %d , %d )", jogador1.coorX, jogador1.coorY);

        // colorirm(mapa[jogador1.coorY][jogador1.coorX]);

        {
            
            for (int ys = 0; ys < MaxY; ys++)
            {
                for (int xs = 0; xs < MaxX; xs++)
                {
                    if (ys != jogador1.coorY || xs != jogador1.coorX)
                    {
                        if(mapa[ys][xs].cor==Visivel) //visivel
                        {
                            attron(COLOR_PAIR(Visivel));
                            mvaddch(ys, xs, mapa[ys][xs].character);
                            attroff(COLOR_PAIR(Visivel));
                        }
                        else if(mapa[ys][xs].cor==Nao_Visivel) //Nao Visivel
                        {
                            attron(COLOR_PAIR(Nao_Visivel));
                            mvaddch(ys, xs, mapa[ys][xs].character);
                            attroff(COLOR_PAIR(Nao_Visivel));
                        }
                        else                        // Ja visto
                        {
                            attron(COLOR_PAIR(Visto));
                            mvaddch(ys, xs, mapa[ys][xs].character);
                            attroff(COLOR_PAIR(Visto));
                        }
                    }
                }
            }
        }
        refresh();
    }
    endwin();
    return 0;
}
