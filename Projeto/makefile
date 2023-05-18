CFLAGS=-Wall -Wextra -pedantic -O2 -g
LIBS=-lm -lcurses

jogo: main.o movimento.o iluminacao.o mapa.o menuhud.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

clean:
	rm jogo *.o
