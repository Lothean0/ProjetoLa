#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "player.h"
#include "mapa.h"

// o ncurses usa ints para fazer pares de cores lolmao
#define Visivel 1
#define Nao_Visivel 2
#define Visto 3

void inicializar_cor(void)
{
    start_color();
    init_pair(Visivel, COLOR_WHITE, COLOR_BLACK);
    init_pair(Nao_Visivel, COLOR_BLACK, COLOR_BLACK);
    init_pair(Visto, COLOR_CYAN, COLOR_BLACK);
}

void colorir(Player *jogador)
{
    jogador->cor = COLOR_PAIR(Visto);
}

void colorirm(Mapa *mapa)
{
    if (mapa->visao == 1)
    {
        mapa->cor = COLOR_PAIR(Visivel);
    }
    else if (mapa->visao == 0)
    {
        mapa->cor = COLOR_PAIR(Nao_Visivel);
    }
    else
    {
        mapa->cor = COLOR_PAIR(Visto);
    }
}

//Visualizaçao feita com um algoritmo de shadowcasting. Basicamente a ideia e ir vendo tudo a volta do player num raio e se encontrarmos parede metemos sombra para tudo que esteja depois dela
void FOV(int player_y, int player_x, Mapa **mapa, int MaxY, int MaxX)
{
    //raio de visao. esta a MaxX para que em teoria se possa ver o mapa todo
    int raio = MaxX;
    //vamos percorrer o mapa e calcular distancias entre celulas do mesmo e o player. dy e a distancia em y e dx a distancia em x
    for(int i=0;i<MaxX;i++)
    {
        for(int j=0;j<MaxY;j++)
        {
            int dy = j - player_y;
            int dx = i - player_x;
            int distancia = dx * dx + dy * dy;
            
            //verificar se a distancia calculada esta dentro do nosso raio de visao
            if(distancia <= raio * raio)
            {
                //encontrar o angulo entre a celula e o jogador. a conta dentro de atan2 e o arctangente do angulo, e o atan2 calcula assim o angulo
                //talvez possamos usar outra maneira para calcular o angulo, com o arcsen ou o arccos
                float angulo = atan2(j-player_y,i-player_x);
                
                //este vai ser o raio de luz a ser lancado pelo player. usamos + 0.5 para conseguirmos atingir todas as celulas que estejam no caminho, incluindo as diagonais
                float oy = player_y + 0.5;
                float ox = player_x + 0.5;
                bool visivel = true;

                //ciclo while que vai percorrer o nosso mapa. vamos parar o ciclo quando ja tivermos percorrido o mapa todo
                while (oy >= 0 && ox >= 0 && oy < MaxY && ox < MaxX)
                {
                    //como a matriz nao trabalha com floats, temos de fazer um cast de float para int das coordenadas a verificar para que o possamos fazer
                    int verY = (int)oy;
                    int verX = (int)ox;

                    //se encontrarmos uma parede, marcamos esse local como nao visivel
                    if(mapa[verY][verX].character == '#')
                    {
                        visivel = false;
                    }

                    //Marcar a visibilidade da celula.
                    mapa[verY][verX].visao = mapa[verY][verX].visao || visivel;

                    //Se a visiblidade da celula e nula, entao podemos interromper o raio de visao
                    if(!visivel)
                    {
                        break;
                    }

                    //Caso seja visivel, avançar com o raio de visao. incrementamos os ox e oy por sin e cos do angulo porque temos de ver tudo a nossa volta
                    //e podemos pensar em coordenadas trigonometricas, em que o x e o cosseno e o y e o seno
                    oy += sin(angulo);
                    ox += cos(angulo);

                }
                
            }
        }
    }
}