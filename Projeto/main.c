#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
// #include <SDL2/SDL.h>
#include "player.h"
#include "mapa.h"
#include "menuhud.h"
#include "inimigo.h"
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

void raio_a_volta(int posicao_y_player, int posicao_x_player, int raio, char g)
{
    //Fazer uma parede de cada vez
    while (raio != 0)
    {
        int parede_atual_x, parede_atual_y;

        // faz as paredes de cima e baixo  (ง ͡❛ ͜ʖ ͡❛)ง

        for (parede_atual_x = posicao_x_player - raio;parede_atual_x <= posicao_x_player + raio; parede_atual_x++){

            mvaddch(posicao_y_player - raio, parede_atual_x, g); // Linha superior do raio
            mvaddch(posicao_y_player + raio, parede_atual_x, g); // Linha inferior do raio
        }

        // faz as paredes dos lados

        for (parede_atual_y = posicao_y_player - raio; (parede_atual_y) <= (posicao_y_player) + raio; parede_atual_y++){

            mvaddch(parede_atual_y, posicao_x_player - raio, g); // Coluna esquerda do raio
            mvaddch(parede_atual_y, posicao_x_player + raio, g); // Coluna direita do raio
        }

        raio--;
    }
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
    startscreen(MaxX, MaxY, win);
    clear();

    //inicializa coisas
    Player jogador1;

    jogo:
    // inicializa o jogador
    jogador1.coorX = 0;
    jogador1.coorY = 0;
    jogador1.hp = 10;
    colorir(&jogador1);

    /*
        void distancia_jogador(int R,int C, int distancia, char *g)
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

    while (jogador1.hp>0)
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
        int qinimigo = rand() % 5 + 5;
        Inimigo inimigo[qinimigo];
        for (int i = 0; i < qinimigo; i++)
        {
            inimigo[i].coorY = 0;
            inimigo[i].coorX = 0;
            inimigo[i].tipo = 0;
            inimigo[i].cor = Nao_Visivel;
            inimigo[i].hp = 10;
            spawnenimigo(&inimigo[i], MaxY, MaxX);
        }

        int tecla;

        // HUD
        hudbox(MaxX, MaxY);

        // ciclo while que corre enquanto a tecla q nao e premida ou enquanto estamos no mesmo floor
        
        while (mapa[jogador1.coorY][jogador1.coorX].character != 'X' && jogador1.hp>=1)
        {
            //eliminar inimigos do arrey
            qsort(inimigo,qinimigo,sizeof(Inimigo), comparehp);
            if (inimigo[qinimigo-1].hp<=0)
            {
                qinimigo--;
            }
            
            // updates ao jogador
            updatehud(MaxX, MaxY, jogador1, FLOOR, win); // HUD
            colorir(&jogador1);


            raio_a_volta(jogador1.coorY, jogador1.coorX, 5, '1');

            // bomba
            if ((tecla = getch()) == 'e')
            {
                bomba(MaxY, MaxX, mapa, jogador1, MaxX);
            }
            //dont mind me
            else if(tecla == 'x')
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
            // print inimigo
            for (int i = 0; i < qinimigo; i++)
            {
                attron(COLOR_PAIR(inimigo[i].cor));
                mvaddch(inimigo[i].coorY, inimigo[i].coorX, '%');
                attroff(COLOR_PAIR(inimigo[i].cor));
            }

            // colorirm(mapa[jogador1.coorY][jogador1.coorX]);
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
        }
        clear();
        MaxX += 25;
        FLOOR -= 1;
        
    }
    int quit = 0;
    while (quit != 'q')
    {
        quit = getch();
        //Go again no jogo
        if(quit == 'r' || quit == 'R')
        {
            goto jogo;
        }
        game_over_screen(MaxY, MaxX);
        refresh();
    }
    clear();
    endwin();
    return 0;
}
