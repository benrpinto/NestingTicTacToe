#include "gameboard.h"
#include <iostream>

using namespace std;
//GameBoard
GameBoard::GameBoard(){

   this->turnTracker = 1;
   for(int a = 0; a < boardWidth; a++ ){
      this->boardSpace.push_back(vector<Position>(boardWidth)); 
   }
   for(int a = 0; a < numPlayers; a++){
      this->myPlayers.push_back(Player(a+1));
   }
}

string GameBoard::display(){
   std::string toReturn = "";
   for(auto& row : this->boardSpace){
      for(auto& cell : row){
         toReturn = toReturn + to_string(cell.myToken.playerID) + " ";
      }
      toReturn = toReturn + "\n";
   }
   return toReturn;
}

//Player
Player::Player(int idIn){
   this->id = idIn;
}
//Position
Position::Position(){
   this->myToken = Token(0,0);
}

//Token
Token::Token(){
   Token(0,0);
}
Token::Token(int sizeIn, int playerIn){
   //TODO: add input validation
   this->size = sizeIn;
   this->playerID = playerIn;
}
