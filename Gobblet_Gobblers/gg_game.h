#pragma once
#include<vector>
#include<string>
#include "gg_board.h"
#include "../basegame.h"
#include "gg_player.h"

//game variables
constexpr bool selfConsume = true;
constexpr bool placeOnly = false;

using namespace std;

class GGBoard;

class GGGame : public BaseGame{
   private:
      vector <GGPlayer> myPlayers;
      GGBoard myBoard;
      int winner;
      bool validMove(int fromX, int fromY, int toX, int toY) const;
      bool validPlace(int posX, int posY, int tokenSize) const;

   public:
      int checkGameEnd();
      GGGame();
      ~GGGame();
      bool validateMove(string move) const;
      bool implementMove(string move);
      pair <bool, int> progressGame();
      string display() const;

   //undo move function
};
