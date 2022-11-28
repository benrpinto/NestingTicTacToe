#include "board.h"
#include "gameboard.h"

//Board
Board::Board(){
   for(int a = 0; a < boardWidth; a++ ){
      this->boardSpace.push_back(vector<Position>(boardWidth)); 
   }
}

string Board::display() const{
   string toReturn = "";
   for(auto& row : boardSpace){
      for(auto& cell : row){
         toReturn += cell.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

bool Board::validatePlace(int posX, int posY, Token toPlace) const{
   bool validMove = true;

   //check that move position is on the board
   validMove &= (posX < boardWidth && posX >= 0);
   validMove &= (posY < boardWidth && posY >= 0);

   validMove &= (toPlace.getSize() <= numSizes);

   //is the token big enough to go there?
   if(validMove){
      validMove &= (toPlace.getSize() > boardSpace[posY][posX].getSize());

      //if self consuming isn't allowed, you can't play on top of your own token
      validMove &= (selfConsume || (toPlace.getPlayer() != boardSpace[posY][posX].getPlayer()));
   }


   return validMove;
}

bool Board::validateMove(int fromX, int fromY, int toX, int toY) const{
   bool validMove = true;
   //check that the from and to positions are on the board
   validMove &= (fromX < boardWidth && fromX >= 0);
   validMove &= (fromY < boardWidth && fromY >= 0);
   validMove &= (toX < boardWidth && toX >= 0);
   validMove &= (toY < boardWidth && toY >= 0);
   if(validMove){
      //check that the token being moved is larger than the token at the destination
      validMove &= (boardSpace[fromY][fromX].getSize() >
         boardSpace[toY][toX].getSize());

      //if self consuming isn't allowed, you can't move on top of your own token
      validMove &= (selfConsume || (boardSpace[fromY][fromX].getPlayer() !=
         boardSpace[toY][toX].getPlayer()));
   }
   return validMove;
}

Token Board::getToken(int posX, int posY) const{
   bool validPos = true;
   int returnSize = 0;
   int returnPlayer = nullPlayer;
   //check that move position is on the board
   validPos &= (posX < boardWidth && posX >= 0);
   validPos &= (posY < boardWidth && posY >= 0);
   if(validPos){
      returnSize = boardSpace[posY][posX].getSize();
      returnPlayer = boardSpace[posY][posX].getPlayer();
   }
   Token toReturn(returnSize,returnPlayer);
   return toReturn;
}

int Board::checkGameEnd(int turnTracker, int winner){
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

void Board::place(int posX, int posY, Token toPlace){
   boardSpace[posY][posX].place(toPlace);
}

void Board::move(int fromX, int fromY, int toX, int toY){
   boardSpace[fromY][fromX].move(boardSpace[toY][toX]);
}
