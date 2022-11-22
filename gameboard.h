#pragma once
#include<vector>
#include<string>
#include "board.h"
#include "player.h"
#include "token.h"
#include "position.h"

//game variables
constexpr int numPlayers = 2;
constexpr int numSizes = 3;
constexpr int sizeCopies = 2;
constexpr bool selfConsume = true;
constexpr bool placeOnly = false;

//signalling constants
constexpr int nullPlayer = -1;
constexpr int inProgress = -1;
constexpr int tieGame = -2;

using namespace std;

class GameBoard{
   private:
      int turnTracker;
      int winner;
      vector<Player> myPlayers;
      Board myBoard;

   public:
      int checkGameEnd();
      bool validateMove(int fromX, int fromY, int toX, int toY) const;
      bool validatePlace(int posX, int posY, int tokenSize) const;

      GameBoard();   
      string display() const;
      pair <bool,int> progressGame();

   //undo move function
};
