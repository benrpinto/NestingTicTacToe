
#pragma once
#include<vector>
#include<string>
#include "../baseplayer.h"
#include "gg_token.h"


constexpr int numSizes = 3;
constexpr int sizeCopies = 2;

using namespace std;

class GGPlayer : BasePlayer{
   protected:
      vector<vector<GGToken>> myTokens;

   public:
      GGPlayer(int idIn);
      bool hasToken(int tokenSize) const;
      bool validateMove(string move) const;
      bool implementMove(string move);
      string display() const;
};
