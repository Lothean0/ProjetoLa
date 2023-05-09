CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o movimento.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
