#pragma once
#include<vector>
#include<string>
#include "gg_token.h"

using namespace std;

class GGPosition{
   protected:
      vector<GGToken> myTokens;

   public:
      GGPosition();
      int getSize() const;
      int getPlayer() const;
      void place(GGToken toPlace);
      void move(GGPosition& destination);
      string display() const;
};
