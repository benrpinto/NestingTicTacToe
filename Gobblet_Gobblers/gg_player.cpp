#include "../basegame.h"
#include "gg_player.h"

using namespace std;

//GGPlayer
GGPlayer::GGPlayer(int idIn){
   id = idIn;
   for(int a = 1; a <= numSizes ; a++){
      vector <GGToken> toAdd;
      for(int b = 0; b < sizeCopies; b++){
         const GGToken Focus(a,id);
         toAdd.push_back(Focus);
      }
      myTokens.push_back(toAdd);
   }
}

GGPlayer::~GGPlayer(){
   myTokens.clear();
}


bool GGPlayer::validateMove(string move) const{
   bool toReturn = true;
   if(move.length() == 3){
      int tokenSize = move.at(2) - '0';
      toReturn = hasToken(tokenSize);
   }
   return toReturn;
}

bool GGPlayer::implementMove(string move){
   bool toReturn = validateMove(move);
   if(toReturn && move.length() == 3){
      int tokenSize = move.at(2) - '0';
      myTokens[tokenSize-1].pop_back();
   }
   return toReturn;
}

string GGPlayer::display() const{
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

bool GGPlayer::hasToken(int tokenSize) const{
   bool toReturn = false;
   if(tokenSize > 0 && tokenSize <= numSizes){
      //tokens range from size 1 to numSize
      //indices start at 0, so subtract 1
      toReturn = !myTokens[tokenSize -1].empty();
   }
   return toReturn;
}
