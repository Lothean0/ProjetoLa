CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o movimento.o iluminacao.o mapa.o
	$(CC) $(CFLAGS) -o -g $@ $^ $(LIBS)

clean:
	rm jogo *.o
