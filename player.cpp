#include "player.h"
#include "gameboard.h"

using namespace std;

//Player
Player::Player(int idIn){
   id = idIn;
   for(int a = 1; a <= numSizes ; a++){
      vector <Token> toAdd;
      for(int b = 0; b < sizeCopies; b++){
         const Token Focus(a,id);
         toAdd.push_back(Focus);
      }
      myTokens.push_back(toAdd);
   }
}

string Player::display() const{
   string toReturn = "";
   toReturn += to_string(id) + "\n";
   for(auto& focusSize : myTokens){
      for(auto& focusToken : focusSize){
         toReturn += focusToken.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

bool Player::hasToken(int tokenSize) const{
   bool toReturn = false;
   if(tokenSize > 0 && tokenSize <= numSizes){
      //tokens range from size 1 to numSize
      //indices start at 0, so subtract 1
      toReturn = !myTokens[tokenSize -1].empty();
   }
   return toReturn;
}

Token Player::playToken(int tokenSize){
   bool hasTok = hasToken(tokenSize);
   Token blank;
   Token toReturn = hasTok? myTokens[tokenSize-1].back():blank;
   if(hasTok){
      myTokens[tokenSize-1].pop_back();
   }
   return toReturn;
}
