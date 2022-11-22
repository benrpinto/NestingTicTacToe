#pragma once
#include<vector>
#include<string>
#include "token.h"

using namespace std;

class Player{
   private:
      vector<vector<Token>> myTokens;
      int id;
//      std::string name

   public:
      Player(int idIn);
      string display() const;
      bool hasToken(int tokenSize) const;
      Token playToken(int tokenSize);
};
