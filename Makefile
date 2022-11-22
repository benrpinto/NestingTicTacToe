.PHONY: all
all: game.out test.out

game: game.out

test: test.out

game.out: main.cpp gameboard.cpp gameboard.h board.cpp board.h	\
		player.cpp player.h position.cpp position.h token.cpp token.h
	g++ -Wall -Werror main.cpp gameboard.cpp board.cpp player.cpp \
		position.cpp token.cpp -o game.out

test.out: test.cpp gameboard.cpp gameboard.h board.cpp board.h \
		player.cpp player.h position.cpp position.h token.cpp token.h
	g++ -Wall -Werror test.cpp gameboard.cpp board.cpp player.cpp \
		position.cpp token.cpp -o test.out

.PHONY: clean
clean:
	rm -f game.out test.out
