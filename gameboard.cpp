#include "gameboard.h"
#include <iostream>

using namespace std;
//GameBoard
GameBoard::GameBoard(){
   turnTracker = 0;
   winner = nullPlayer;
   for(int a = 0; a < numPlayers; a++){
      myPlayers.push_back(Player(a));
   }
}

string GameBoard::display() const{
   string toReturn = "";
   for(auto& focusPlayer : myPlayers){
      toReturn += focusPlayer.display();
   }
   toReturn += myBoard.display();
   return toReturn;
}

pair <bool,int> GameBoard::progressGame(){
   string input;
   int posX;
   int posY;
   int fromX;
   int fromY;
   int toX;
   int toY;
   int tokenSize;
   bool validMove = false;
   int victor;

   getline(cin,input);
   if(input == "q"){
//quitting is always a valid mov
      validMove = true;
//will have to change to accommodate for more than 2 players
      winner = (turnTracker + 1) % numPlayers;
   }else if(input.length() == 3){
//extract data from user input
      posX = input.at(0) - '0';
      posY = input.at(1) - '0';
//0 is bottom for the user, but top for us
      posY = boardWidth - posY - 1;
      tokenSize = input.at(2) - '0';
      validMove = validatePlace(posX, posY, tokenSize);
      if(validMove){
         Token toPlay = myPlayers[turnTracker].playToken(tokenSize);
         if(toPlay.getPlayer() != nullPlayer){
            myBoard.place(posX,posY,toPlay);
         }
      }
   }else if(input.length() == 5){
      fromX = input.at(0) - '0';
      fromY = input.at(1) - '0';
      fromY = boardWidth - fromY - 1;
      toX = input.at(3) - '0';
      toY = input.at(4) - '0';
      toY = boardWidth - toY - 1;
      validMove = input.at(2) == ' ';
      validMove &= validateMove(fromX,fromY,toX,toY);
      if(validMove){
         myBoard.move(fromX,fromY,toX,toY);
      }
   }else{
      validMove = false;
   }
   if(!validMove){
      cout<<"Invalid Move\n";
   }
   
   if(validMove){
      victor = checkGameEnd();
      turnTracker = (turnTracker + 1) % numPlayers;
   }else{
      victor = winner;
   }
   return make_pair(validMove,victor);
}

bool GameBoard::validateMove(int fromX, int fromY, int toX, int toY) const{
   bool validMove = true;
   Token toMove;
   validMove &= myBoard.validateMove(fromX,fromY,toX,toY);

   //check that the player owns the token being moved
   validMove &= (myBoard.getToken(fromX,fromY).getPlayer() == turnTracker);
   
   return validMove;
}

bool GameBoard::validatePlace(int posX, int posY, int tokenSize) const{
   bool validMove = true;

   //you can only play tokens you have
   validMove &= myPlayers[turnTracker].hasToken(tokenSize);
   if(validMove){
      Token toPlace(tokenSize,turnTracker);
      validMove &= myBoard.validatePlace(posX,posY,toPlace);
   }
   return validMove;
}

int GameBoard::checkGameEnd(){
   return myBoard.checkGameEnd(turnTracker,winner);
}



