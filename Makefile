.PHONY: all
all: gobblet_gobblers.out gobblet_gobblers_test.out

gobblet_gobblers: gobblet_gobblers.out

gobblet_gobblers_test: gobblet_gobblers_test.out

gobblet_gobblers.out: main.cpp \
		baseboard.cpp baseboard.h \
		basegame.cpp basegame.h \
		Gobblet_Gobblers/gg_game.cpp Gobblet_Gobblers/gg_game.h \
		Gobblet_Gobblers/gg_board.cpp Gobblet_Gobblers/gg_board.h \
		Gobblet_Gobblers/gg_player.cpp Gobblet_Gobblers/gg_player.h \
		Gobblet_Gobblers/gg_position.cpp Gobblet_Gobblers/gg_position.h \
		Gobblet_Gobblers/gg_token.cpp Gobblet_Gobblers/gg_token.h
	g++ -Wall -Werror main.cpp \
		Gobblet_Gobblers/gg_game.cpp \
		baseboard.cpp \
		basegame.cpp \
		Gobblet_Gobblers/gg_board.cpp \
		Gobblet_Gobblers/gg_player.cpp \
		Gobblet_Gobblers/gg_position.cpp \
		Gobblet_Gobblers/gg_token.cpp \
		-o gobblet_gobblers.out

gobblet_gobblers_test.out:	Gobblet_Gobblers/gg_test.cpp Gobblet_Gobblers/gg_test.h \
		baseboard.cpp baseboard.h \
		basegame.cpp basegame.h \
		Gobblet_Gobblers/gg_game.cpp Gobblet_Gobblers/gg_game.h \
		Gobblet_Gobblers/gg_board.cpp Gobblet_Gobblers/gg_board.h \
		Gobblet_Gobblers/gg_player.cpp Gobblet_Gobblers/gg_player.h \
		Gobblet_Gobblers/gg_position.cpp Gobblet_Gobblers/gg_position.h \
		Gobblet_Gobblers/gg_token.cpp Gobblet_Gobblers/gg_token.h
	g++ -Wall -Werror Gobblet_Gobblers/gg_test.cpp \
		Gobblet_Gobblers/gg_game.cpp \
		baseboard.cpp \
		basegame.cpp \
		Gobblet_Gobblers/gg_board.cpp \
		Gobblet_Gobblers/gg_player.cpp \
		Gobblet_Gobblers/gg_position.cpp \
		Gobblet_Gobblers/gg_token.cpp \
		-o gobblet_gobblers_test.out

.PHONY: clean
clean:
	rm -f gobblet_gobblers.out gobblet_gobblers_test.out
