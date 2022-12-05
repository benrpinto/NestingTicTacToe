#include "../basegame.h"
#include "gg_board.h"
#include "gg_game.h"
#include<iostream>

using namespace std;
//GGBoard
GGBoard::GGBoard(){
   for(int a = 0; a < boardWidth; a++ ){
      boardSpace.push_back(vector<GGPosition>(boardWidth)); 
   }
}

GGBoard::~GGBoard(){
   for(int a = 0; a < boardWidth; a++ ){
      boardSpace[a].clear(); 
   }
   boardSpace.clear();
   
}

string GGBoard::display() const{
   string toReturn = "";
   for(auto& row : boardSpace){
      for(auto& cell : row){
         toReturn += cell.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

bool GGBoard::validateMove(string input, int curPlayer) const{
   int posX;
   int posY;
   int fromX;
   int fromY;
   int toX;
   int toY;
   int tokenSize;
   bool toReturn = false;
   
   if(input == "q"){
//quitting is always a valid mov
      toReturn = true;
   }else if(input.length() == 3){
//extract data from user input
      posX = input.at(0) - '0';
      posY = input.at(1) - '0';
//0 is bottom for the user, but top for us
      posY = boardWidth - posY - 1;
      tokenSize = input.at(2) - '0';
      GGToken toPlace(tokenSize,curPlayer);
      toReturn = validPlace(posX, posY, toPlace);
   }else if(input.length() == 5){
      fromX = input.at(0) - '0';
      fromY = input.at(1) - '0';
      fromY = boardWidth - fromY - 1;
      toX = input.at(3) - '0';
      toY = input.at(4) - '0';
      toY = boardWidth - toY - 1;
      toReturn = input.at(2) == ' ';
      toReturn &= validMove(fromX,fromY,toX,toY);
   }else{
      toReturn = false;
   } 
   return toReturn;
}

bool GGBoard::implementMove(string move, int curPlayer){
   int posX;
   int posY;
   int fromX;
   int fromY;
   int toX;
   int toY;
   int tokenSize;
   bool toReturn;
   toReturn = validateMove(move,curPlayer);
   if(toReturn == false){
// invalid move, don't do anything.
   }else if(move.length() == 3){
//extract data from user input
      posX = move.at(0) - '0';
      posY = move.at(1) - '0';
//0 is bottom for the user, but top for us
      posY = boardWidth - posY - 1;
      tokenSize = move.at(2) - '0';
      GGToken toPlace(tokenSize,curPlayer);
      place(posX, posY, toPlace);
   }else if(move.length() == 5){
      fromX = move.at(0) - '0';
      fromY = move.at(1) - '0';
      fromY = boardWidth - fromY - 1;
      toX = move.at(3) - '0';
      toY = move.at(4) - '0';
      toY = boardWidth - toY - 1;
      this->move(fromX,fromY,toX,toY);
   } 
   return toReturn;
}


bool GGBoard::validPlace(int posX, int posY, GGToken toPlace) const{
   bool toReturn = true;

   //location checks
   toReturn = toReturn && (posX < boardWidth && posX >= 0);
   toReturn = toReturn && (posY < boardWidth && posY >= 0);

   //size checks
   toReturn = toReturn && (toPlace.getSize() <= numSizes);
   toReturn = toReturn && 
      (toPlace.getSize() > boardSpace[posY][posX].getSize());

   //if self consuming isn't allowed, you can't play on top of your own token
   toReturn = toReturn && (selfConsume || 
         (toPlace.getPlayer() != boardSpace[posY][posX].getPlayer()));

   return toReturn;
}

bool GGBoard::validMove(int fromX, int fromY, int toX, int toY) const{
   bool toReturn = true;

   //location checks
   toReturn = toReturn && (fromX < boardWidth && fromX >= 0);
   toReturn = toReturn && (fromY < boardWidth && fromY >= 0);
   toReturn = toReturn && (toX < boardWidth && toX >= 0);
   toReturn = toReturn && (toY < boardWidth && toY >= 0);

   //size check
   toReturn = toReturn && (boardSpace[fromY][fromX].getSize() >
         boardSpace[toY][toX].getSize());

   //if self consuming isn't allowed, you can't move on top of your own token
   toReturn = toReturn && (selfConsume || (boardSpace[fromY][fromX].getPlayer() !=
         boardSpace[toY][toX].getPlayer()));
   return toReturn;
}

GGToken GGBoard::getToken(int posX, int posY) const{
   bool validPos = true;
   int returnSize = 0;
   int returnPlayer = nullPlayer;

   //location check
   validPos = validPos && (posX < boardWidth && posX >= 0);
   validPos = validPos && (posY < boardWidth && posY >= 0);

   if(validPos){
      returnSize = boardSpace[posY][posX].getSize();
      returnPlayer = boardSpace[posY][posX].getPlayer();
   }

   GGToken toReturn(returnSize,returnPlayer);
   return toReturn;
}

int GGBoard::checkGameEnd(int turnTracker, int winner){
   vector<int> playerVictory(numPlayers);
   int counter = 0;
   int focusPlayer = nullPlayer;
   int currentPlayer = nullPlayer;
   int row;
   int col;
   for(auto& x : playerVictory){
      x = false;
   }
   if(winner != nullPlayer){
      playerVictory[winner] = true;
   }

   if(winner == nullPlayer){
      //check rows for 3-in-a-row
      for(row = 0; row < boardWidth; row++){
         counter = 0;
         focusPlayer = nullPlayer;
         for(col = 0; col < boardWidth; col++){
            currentPlayer = boardSpace[row][col].getPlayer();
            if(focusPlayer == currentPlayer){
               counter++;
            }else{
               counter = 1;
               focusPlayer = currentPlayer;
            }
            if(counter == 3 && focusPlayer != nullPlayer){
               playerVictory[focusPlayer] = true;
            }
         }
      }

      //check cols for 3-in-a-row
      for(col = 0; col < boardWidth; col++){
         counter = 0;
         focusPlayer = nullPlayer;
         for(row = 0; row < boardWidth; row++){
            currentPlayer = boardSpace[row][col].getPlayer();
            if(focusPlayer == currentPlayer){
               counter++;
            }else{
               counter = 1;
               focusPlayer = currentPlayer;
            }
            if(counter == 3 && focusPlayer != nullPlayer){
               playerVictory[focusPlayer] = true;
            }
         }
      }

      //check diagonal for 3 in a row
      for(int a = 0; a < boardWidth; a++){
         counter = 0;
         focusPlayer = nullPlayer;
         for(int b = 0; b < boardWidth; b++){
            row = b % boardWidth;
            col = (a + b) % boardWidth;
            currentPlayer = boardSpace[row][col].getPlayer();
            if((row == 0) || (col == 0) || (currentPlayer != focusPlayer)){
               focusPlayer = currentPlayer;
               counter = 1;
            }else{
               counter++;
            }
            if(counter >= 3 && focusPlayer != nullPlayer){
               playerVictory[focusPlayer] = true;
            }
         }
      }

      //check other diagonal for 3 in a row
      for(int a = 0; a < boardWidth; a++){
         counter = 0;
         focusPlayer = nullPlayer;
         for(int b = 0; b < boardWidth; b++){
            row = boardWidth - 1 - (b % boardWidth);
            col = ((a + b) % boardWidth);
            currentPlayer = boardSpace[row][col].getPlayer();
            if((row == boardWidth -1) || (col == 0) || (currentPlayer != focusPlayer)){
               focusPlayer = currentPlayer;
               counter = 1;
            }else{
               counter++;
            }
            if(counter >= 3 && focusPlayer != nullPlayer){
               playerVictory[focusPlayer] = true;
            }
         }
      }
   }

   for(int a = 1; (a <= numPlayers) && (winner == nullPlayer); a++){
      if(playerVictory[(turnTracker + a) % numPlayers]){
         winner = (turnTracker + a) % numPlayers;
      }
   }
   return winner;
}

void GGBoard::place(int posX, int posY, GGToken toPlace){
   boardSpace[posY][posX].place(toPlace);
}

void GGBoard::move(int fromX, int fromY, int toX, int toY){
   boardSpace[fromY][fromX].move(boardSpace[toY][toX]);
}
