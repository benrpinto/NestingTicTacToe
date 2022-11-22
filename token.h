#pragma once
#include<string>

using namespace std;

class Token{
   private:
      const int size;
      const int playerID;

   public:
      Token();
      Token(int sizeIn, int playerIn);
      int getSize() const;
      int getPlayer() const;
      string display() const;
};

