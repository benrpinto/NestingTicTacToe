.PHONY: all
all: gobblet_gobblers.out gobblet_gobblers_test.out

gobblet_gobblers: game.out

gobblet_gobblers_test: test.out

gobblet_gobblers.out: main.cpp Gobblet_Gobblers/gameboard.cpp Gobblet_Gobblers/gameboard.h Gobblet_Gobblers/board.cpp Gobblet_Gobblers/board.h	\
		Gobblet_Gobblers/player.cpp Gobblet_Gobblers/player.h Gobblet_Gobblers/position.cpp Gobblet_Gobblers/position.h Gobblet_Gobblers/token.cpp Gobblet_Gobblers/token.h
	g++ -Wall -Werror main.cpp Gobblet_Gobblers/gameboard.cpp Gobblet_Gobblers/board.cpp Gobblet_Gobblers/player.cpp \
		Gobblet_Gobblers/position.cpp Gobblet_Gobblers/token.cpp -o gobblet_gobblers.out

gobblet_gobblers_test.out: Gobblet_Gobblers/test.cpp Gobblet_Gobblers/gameboard.cpp Gobblet_Gobblers/gameboard.h Gobblet_Gobblers/board.cpp Gobblet_Gobblers/board.h \
		Gobblet_Gobblers/player.cpp Gobblet_Gobblers/player.h Gobblet_Gobblers/position.cpp Gobblet_Gobblers/position.h Gobblet_Gobblers/token.cpp Gobblet_Gobblers/token.h
	g++ -Wall -Werror Gobblet_Gobblers/test.cpp Gobblet_Gobblers/gameboard.cpp Gobblet_Gobblers/board.cpp Gobblet_Gobblers/player.cpp \
		Gobblet_Gobblers/position.cpp Gobblet_Gobblers/token.cpp -o gobblet_gobblers_test.out

.PHONY: clean
clean:
	rm -f game.out test.out
