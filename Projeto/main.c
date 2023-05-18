#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
// #include <SDL2/SDL.h>
#include "player.h"
#include "mapa.h"
#include "menuhud.h"

/*SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;*/

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

    // inicializa o jogador
    Player jogador1;
    jogador1.coorX = 0;
    jogador1.coorY = 0;
    colorir(&jogador1);

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
    startscreen(MaxX, MaxY, win);
    clear();

    /*
        typedef struct raio_distancia{
            char g;
            int monstro;
        }Raio_Dist;

        void distancia_jogador(int R,int C, int distancia, Raio_Dist *g)
        {
            //imprimir varios circulos com raio 1- raio 2- raio-3 raio-4 etc
            //Condicoes- Paredes, outros circulos e atingir a distancia maxima

            if(distancia > 20) return;                                      // atingiu a distancia maxima ou nao
            if(g->mapa[R][C].character = '#') return;                       // se for parede
            if(g->mapa[R][C].distancia <= distancia) return;                // se for outro circulo
            g->mapa[R][C].distancia = valor;                                // passou as outras condicoes ent avanca

            printw("%d", mapa[R][C].distancia);
        }
    */

    // Floors armazena o floor em que o jogador esta
    int FLOOR = 0;

    while (1)
    {
        MaxX -= 25; // Faz com que o mapa tenha -25 casas que a win (25 casas para o hud )
        
        // geracao de mapa
        Mapa mapa[MaxY][MaxX];
        gera_mapa(MaxY, MaxX, mapa);
        denoiser(MaxY, MaxX, mapa);
        gerahole(MaxY, MaxX, mapa);
        imprime(MaxY, MaxX, mapa, win);

        // coloca o jogador numa posicao random do ecra
        spawn(&jogador1, MaxY, MaxX);
        mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
        int tecla;

        //HUD
        hudbox(MaxX,MaxY);

        // ciclo while que corre enquanto a tecla q nao e premida ou enquanto estamos no mesmo floor
        while (mapa[jogador1.coorY][jogador1.coorX].character != 'X')
        {
            // updates ao jogador
            updatehud(MaxX, MaxY, jogador1, FLOOR, win); //HUD
            colorir(&jogador1);
            //distancia_jogador(jogador1.coorY, jogador1.coorX, 20, g);     ////////////////////////////////////////funcao distancia de jogador aqui///////////////////////////////////

            // bomba
            if ((tecla = getch()) == 'e')
            {
                bomba(MaxY, MaxX, mapa, jogador1, MaxX);
            }else // ou movimento
            {
                mudarstate(&jogador1, MaxX, tecla, mapa);
            }

            // print player
            attron(jogador1.cor);
            mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
            attroff(jogador1.cor);

            // Visao
            FOV(jogador1.coorY, jogador1.coorX, MaxY, MaxX, mapa);

            refresh();

            // colorirm(mapa[jogador1.coorY][jogador1.coorX]);
            for (int ys = 0; ys < MaxY; ys++)
            {
                for (int xs = 0; xs < MaxX; xs++)
                {
                    if (ys != jogador1.coorY || xs != jogador1.coorX)
                    {
                        attron(COLOR_PAIR(mapa[ys][xs].cor)); // Da print em cada character com a sua propria cor
                        mvaddch(ys, xs, mapa[ys][xs].character);
                        attroff(COLOR_PAIR(mapa[ys][xs].cor));
                    }
                }
            }
            refresh();
        }
        clear();
        MaxX += 25;
        FLOOR -= 1;
    }
    endwin();
    return 0;
}
