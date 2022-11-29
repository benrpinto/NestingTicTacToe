#include<iostream>
#include<string>
#include "basegame.h"

pair <bool,int> BaseGame::progressGame(){
   pair<bool, int> toReturn;
   string input;

   getline(cin,input);
   if(input == "q"){
//quitting is always a valid move
      toReturn.first = true;
      toReturn.second = (turnTracker + 1) % numPlayers;
   }else{
      toReturn.first = validateMove(input);
      if(toReturn.first){
         toReturn.first = implementMove(input);
         toReturn.second = checkGameEnd();
      }else{
         toReturn.first = false;
         toReturn.second = checkGameEnd();
      }
   }
   return toReturn;
}
