#pragma once
#include<vector>
#include<string>
#include "../baseboard.h"
#include "gg_position.h"
#include "gg_token.h"


constexpr int boardWidth = 3;

using namespace std;

class GGBoard : public BaseBoard{
   protected:
      vector<vector<GGPosition>> boardSpace;
      void place(int posX,int posY,GGToken toPlace);
      void move(int fromX, int fromY, int toX, int toY);
      GGToken getToken(int posX, int posY) const;

   public:
      GGBoard();
      ~GGBoard();
      int checkGameEnd(int currentPlayer, int victor);
      bool validMove(int fromX, int fromY, int toX, int toY) const;
      bool validPlace(int posX, int posY, GGToken toPlace) const;
      bool validateMove(string move, int curPlayer) const;
      bool implementMove(string move, int curPlayer);
      string display() const;
};

