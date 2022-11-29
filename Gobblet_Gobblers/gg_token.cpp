#include "gg_token.h"
#include "../basegame.h"

using namespace std;

//Token
GGToken::GGToken():size(0),playerID(nullPlayer){}

GGToken::GGToken(int sizeIn, int playerIn):size(sizeIn),playerID(playerIn){}

string GGToken::display() const{
   string toReturn = "";
   if(playerID == nullPlayer){
      toReturn = "./.";
   }else{
      toReturn = to_string(size) + "/" + to_string(playerID);
   }
   return toReturn;
}

int GGToken::getSize() const{
   return size;
}

int GGToken::getPlayer() const{
   return playerID;
}
