#pragma once
#include <string>

//constants
constexpr int numPlayers = 2;

//signalling constants
constexpr int nullPlayer = -1;
constexpr int inProgress = -1;
constexpr int tieGame = -2;

using namespace std;

class BaseGame{
   protected:
      int turnTracker;
      virtual bool implementMove(string move) = 0;

   public:
      virtual int checkGameEnd() = 0;
      virtual bool validateMove(string move) const = 0;
      virtual pair <bool, int> progressGame();
};
