#pragma once
#include<string>

using namespace std;

class GGToken{
   private:
      const int size;
      const int playerID;

   public:
      GGToken();
      GGToken(int sizeIn, int playerIn);
      int getSize() const;
      int getPlayer() const;
      string display() const;
};

