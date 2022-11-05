#include "gameboard.h"
#include <iostream>

using namespace std;
//GameBoard
GameBoard::GameBoard(){

   this->turnTracker = 0;
   for(int a = 0; a < boardWidth; a++ ){
      this->boardSpace.push_back(vector<Position>(boardWidth)); 
   }
   for(int a = 0; a < numPlayers; a++){
      this->myPlayers.push_back(Player(a));
   }
}

string GameBoard::display(){
   string toReturn = "";
   for(auto& focusPlayer : this->myPlayers){
      toReturn += focusPlayer.display();
   }
   for(auto& row : this->boardSpace){
      for(auto& cell : row){
         toReturn += cell.myToken.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

//Player
Player::Player(int idIn){
   this->id = idIn;
   for(int a = 0; a < numSizes ; a++){
      vector <Token> toAdd;
      for(int b = 0; b < sizeCopies; b++){
         Token Focus(this->id,a);
         toAdd.push_back(Focus);
      }
      this->myTokens.push_back(toAdd);
   }
}

string Player::display(){
   string toReturn = "";
   toReturn += to_string(this->id) + "\n";
   for(auto& focusSize : this->myTokens){
      for(auto& focusToken : focusSize){
         toReturn += focusToken.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

//Position
Position::Position(){
   this->myToken = Token(0, nullPlayer);
}

//Token
Token::Token(){
   Token(0,nullPlayer);
}
Token::Token(int sizeIn, int playerIn){
   //TODO: add input validation
   this->size = sizeIn;
   this->playerID = playerIn;
}

string Token::display(){
   string toReturn = "";
   if(this->playerID == nullPlayer){
      toReturn = "./.";
   }else{
      toReturn = to_string(this->size) + "/" + to_string(this->playerID);
   }
   return toReturn;
}
