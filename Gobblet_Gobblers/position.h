#pragma once
#include<vector>
#include<string>
#include "token.h"

using namespace std;

class Position{
   private:
      vector<Token> myTokens;

   public:
      Position();
      int getSize() const;
      int getPlayer() const;
      void place(Token toPlace);
      void move(Position& destination);
      string display() const;
};
