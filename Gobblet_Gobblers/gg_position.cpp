#include "gg_position.h"
#include "../basegame.h"

using namespace std;

//GGPosition
GGPosition::GGPosition(){
   myTokens.push_back(GGToken(0, nullPlayer));
}

int GGPosition::getSize() const{
   GGToken topToken = myTokens.back();
   return topToken.getSize();
}

int GGPosition::getPlayer() const{
   GGToken topToken = myTokens.back();
   return topToken.getPlayer();
}

void GGPosition::place(GGToken toPlace){
   myTokens.push_back(toPlace);
}

void GGPosition::move(GGPosition& destination){
   destination.place(myTokens.back());
   myTokens.pop_back();
}


string GGPosition::display() const{
   GGToken topToken = myTokens.back();
   return topToken.display();
}
