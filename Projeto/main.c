#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
// #include <SDL2/SDL.h>
#include "player.h"
#include "mapa.h"

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
        mvprintw((MaxY / 2) + 8, (MaxX / 2) - 12, "                                                    _..._                                                       ");
        mvprintw((MaxY / 2) + 9, (MaxX / 2) - 12, "                                                 .-'_..._''.                .---..---.                          ");
        mvprintw((MaxY / 2) + 10, (MaxX / 2) - 12, "/|        .--.   _..._                         .' .'      '.\\  .        .--.|   ||   |.--.   _..._              ");
        mvprintw((MaxY / 2) + 11, (MaxX / 2) - 12, "||        |__| .'     '.   .--./)             / .'           .'|        |__||   ||   ||__| .'     '.   .--./)   ");
        mvprintw((MaxY / 2) + 12, (MaxX / 2) - 12, "||        .--..   .-.   . /.''\\             . '            <  |        .--.|   ||   |.--..   .-.   . /.''\\    ");
        mvprintw((MaxY / 2) + 13, (MaxX / 2) - 12, "||  __    |  ||  '   '  || |  | |            | |             | |        |  ||   ||   ||  ||  '   '  || |  | ||   ");
        mvprintw((MaxY / 2) + 14, (MaxX / 2) - 12, "||/'__ '. |  ||  |   |  | \\`-' /             | |             | | .'''-. |  ||   ||   ||  ||  |   |  | \\`-' /    ");
        mvprintw((MaxY / 2) + 15, (MaxX / 2) - 12, "|:/`  '. '|  ||  |   |  | /(\"'`              . '             | |/.'''. \\|  ||   ||   ||  ||  |   |  | /(\"'`     ");
        mvprintw((MaxY / 2) + 16, (MaxX / 2) - 12, "||     | ||  ||  |   |  | \\ '---.             \\ '.          .|  /    | ||  ||   ||   ||  ||  |   |  | \\ '---.   ");
        mvprintw((MaxY / 2) + 17, (MaxX / 2) - 12, "||\\    / '|__||  |   |  |  /''.\\             '. `._____.-'/| |     | ||__||   ||   ||__||  |   |  |  /''.\\  ");
        mvprintw((MaxY / 2) + 18, (MaxX / 2) - 12, "|/\'..' /     |  |   |  | ||     ||              `-.______ / | |     | |    '---''---'    |  |   |  | ||     || ");
        mvprintw((MaxY / 2) + 19, (MaxX / 2) - 12, "'  `'-'`      |  |   |  | \'. __//                        `  | '.    | '.                 |  |   |  | \'. __//  ");
        mvprintw((MaxY / 2) + 20, (MaxX / 2) - 12, "              '--'   '--'  `'---'                            '---'   '---'                '--'   '--'  `'---'   ");
        mvprintw((MaxY / 2) + 21, (MaxX / 2) - 12, "                                                                                                                 ");
        refresh();
    }

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

    // while para refazer mapa chegando a um 'X';

    // Floors armazena o floor em que o jogador esta
    int FLOOR = 0;

    while (1)
    {

        // HUD
        MaxX -= 25; // Faz com que o mapa tenha -20 casas que a win (20 casas para o hud )
        // int HudY = 0; // posiçoes do hud (canto sup esquerdo)
        int HudX = MaxX;
        int MaxHudY = MaxY - 1;
        int MaxHudX = HudX + 24;

        mvhline(0, HudX, '_', 24);        // linha de cima
        mvhline(MaxY - 1, HudX, '_', 24); // linha de baixo
        mvvline(0, HudX, '|', MaxY);      // linha da esquerda
        mvvline(0, MaxHudX, '|', MaxY);   // linha da direita

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

        // ciclo while que corre enquanto a tecla q nao e premida ou enquanto estamos no mesmo floor
        while (mapa[jogador1.coorY][jogador1.coorX].character != 'X')
        {
            // updates ao jogador
            colorir(&jogador1);
            //           distancia_jogador(jogador1.coorY, jogador1.coorX, 20, g);     ////////////////////////////////////////funcao distancia de jogador aqui///////////////////////////////////

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
                                if (ys > 0 && xs > 0 && ys < MaxY - 1 && xs < MaxX - 1 && mapa[ys][xs].character != 'X')
                                {
                                    mapa[ys][xs].character = '.';
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                mudarstate(&jogador1, MaxX, tecla, mapa);
            }
            // move(jogador1.coorY, jogador1.coorX);
            attron(jogador1.cor);
            mvaddch(jogador1.coorY, jogador1.coorX, '@' | A_BOLD);
            attroff(jogador1.cor);
            FOV(jogador1.coorY, jogador1.coorX, MaxY, MaxX, mapa);
            refresh();

            // Updates do hud #####
            // Posiçao base da box do hud é (HudY, HudX) Posiçao Max (MaxHudY, MaxHudX)

            mvprintw(4, HudX + 7, "JOGADOR 1");
            mvprintw(7, HudX + 4, "POS : ( %d , %d )  ", jogador1.coorX, jogador1.coorY);
            mvprintw(MaxHudY - 3, HudX + 6, "FLOOR ( %d )  ", FLOOR);

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
