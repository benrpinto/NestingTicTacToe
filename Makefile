.RECIPEPREFIX = >
all: game test

game: gameboard.cpp
>g++ -Wall -Werror main.cpp gameboard.cpp -o ttt.out

test: test.cpp
>g++ -Wall -Werror test.cpp gameboard.cpp -o test.out

clean:
>rm -f test.out ttt.out
