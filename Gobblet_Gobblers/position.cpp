#include "position.h"
#include "gameboard.h"

using namespace std;

//Position
Position::Position(){
   myTokens.push_back(Token(0, nullPlayer));
}

int Position::getSize() const{
   Token topToken = myTokens.back();
   return topToken.getSize();
}

int Position::getPlayer() const{
   Token topToken = myTokens.back();
   return topToken.getPlayer();
}

void Position::place(Token toPlace){
   myTokens.push_back(toPlace);
}

void Position::move(Position& destination){
   destination.place(myTokens.back());
   myTokens.pop_back();
}

string Position::display() const{
   Token topToken = myTokens.back();
   return topToken.display();
}

