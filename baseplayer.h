#pragma once
#include<vector>
#include<string>

using namespace std;

class BasePlayer{
   protected:
      int id;
//      std::string name

   public:
      virtual bool validateMove(string move) const = 0;
      virtual bool implementMove(string move) = 0;
};
