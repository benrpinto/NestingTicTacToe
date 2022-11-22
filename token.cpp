#include "token.h"
#include "gameboard.h"

using namespace std;

//Token
Token::Token():size(0),playerID(nullPlayer){}

Token::Token(int sizeIn, int playerIn):size(sizeIn),playerID(playerIn){}

string Token::display() const{
   string toReturn = "";
   if(playerID == nullPlayer){
      toReturn = "./.";
   }else{
      toReturn = to_string(size) + "/" + to_string(playerID);
   }
   return toReturn;
}

int Token::getSize() const{
   return size;
}

int Token::getPlayer() const{
   return playerID;
}
