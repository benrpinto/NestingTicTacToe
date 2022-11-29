#pragma once
#include<string>

using namespace std;

class BaseBoard {
   public:
      virtual bool validateMove(string move, int curPlayer) const = 0;
      virtual bool implementMove(string move, int curPlayer) = 0;

};
