#include <iostream>
#include "gg_game.h"

using namespace std;
//Game
GGGame::GGGame(){
   turnTracker = 0;
   winner = nullPlayer;
   for(int a = 0; a < numPlayers; a++){
      myPlayers.push_back(GGPlayer(a));
   }
}

GGGame::~GGGame(){
   myPlayers.pop_back();
   myPlayers.pop_back();
}

pair <bool,int> GGGame::progressGame(){
   string input;
   bool validMove = false;

   getline(cin,input);
   if(input == "q"){
//quitting is always a valid mov
      validMove = true;
      winner = (turnTracker + 1) % numPlayers;
   }else{
      validMove = validateMove(input);
   }
   if(validMove){
      implementMove(input);
      winner = checkGameEnd();
      turnTracker = (turnTracker + 1) % numPlayers;
   }else{
      cout<<"Invalid Move\n";
   }
   
   return make_pair(validMove,winner);
}

bool GGGame::validateMove(string input) const{
   bool toReturn = true;

   if(input == "q"){
//quitting is always a valid move
      toReturn = true;
   }else if(input.length() == 3){
      toReturn = toReturn && myBoard.validateMove(input,turnTracker);
      toReturn = toReturn && myPlayers[turnTracker].validateMove(input);
   }else if(input.length() == 5){
      toReturn = toReturn && myBoard.validateMove(input,turnTracker);
   }else{
      toReturn = false;
   }
   return toReturn;
}

bool GGGame::implementMove(string move){
   bool toReturn = true;

   toReturn = myBoard.implementMove(move,turnTracker);
   if(move.length() == 3){
      toReturn = toReturn && myPlayers[turnTracker].implementMove(move);
   }
   return toReturn;
}

int GGGame::checkGameEnd(){
   return myBoard.checkGameEnd(turnTracker,winner);
}


string GGGame::display() const{
   string toReturn = "";
   for(auto& focusPlayer : myPlayers){
      toReturn += focusPlayer.display();
   }
   toReturn += myBoard.display();
   return toReturn;
}

