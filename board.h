#pragma once
#include<vector>
#include<string>
#include "token.h"
#include "position.h"


constexpr int boardWidth = 3;

class Board{
   private:
      vector<vector<Position>> boardSpace;

   public:
      Board();
      string display() const;
      bool validateMove(int fromX, int fromY, int toX, int toY) const;
      bool validatePlace(int posX, int posY, Token toPlace) const;
      void place(int posX,int posY,Token toPlace);
      void move(int fromX, int fromY, int toX, int toY);
      int checkGameEnd(int currentPlayer, int victor);
      Token getToken(int posX, int posY) const;
};

