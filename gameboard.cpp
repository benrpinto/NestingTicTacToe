#include "gameboard.h"
#include <iostream>

using namespace std;
//GameBoard
GameBoard::GameBoard(){
   this->turnTracker = 0;
   this->winner = nullPlayer;
   for(int a = 0; a < numPlayers; a++){
      this->myPlayers.push_back(Player(a));
   }
}

string GameBoard::display(){
   string toReturn = "";
   for(auto& focusPlayer : myPlayers){
      toReturn += focusPlayer.display();
   }
   toReturn += myBoard.display();
   return toReturn;
}

int GameBoard::progressGame(){
   string input;
   int posX;
   int posY;
   int fromX;
   int fromY;
   int toX;
   int toY;
   int tokenSize;
   bool validMove = false;

   while(!validMove){
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
         validMove = validateMove(fromX,fromY,toX,toY);
         if(validMove){
            myBoard.move(fromX,fromY,toX,toY);
         }
      }else{
         validMove = false;
      }
      if(!validMove){
         cout<<"Invalid Move\n";
      }
   }
   int toReturn = checkGameEnd();
   turnTracker = (turnTracker + 1) % numPlayers;
   return toReturn;
}

bool GameBoard::validateMove(int fromX, int fromY, int toX, int toY){
   bool validMove = true;
   Token toMove;
   validMove &= myBoard.validateMove(fromX,fromY,toX,toY);

   //check that the player owns the token being moved
   if(validMove){
      toMove = myBoard.getToken(fromX,fromY);
   }
   validMove &= (toMove.getPlayer() == turnTracker);

   return validMove;
}

bool GameBoard::validatePlace(int posX, int posY, int tokenSize){
   bool validMove = true;
   Token toPlace;

   //you can only play tokens you have
   validMove &= myPlayers[turnTracker].hasToken(tokenSize);
   if(validMove){
      toPlace = Token(tokenSize,turnTracker);
   }
   validMove &= myBoard.validatePlace(posX,posY,toPlace);

   return validMove;
}

int GameBoard::checkGameEnd(){
   return myBoard.checkGameEnd(turnTracker,winner);
}

//Board
Board::Board(){
   for(int a = 0; a < boardWidth; a++ ){
      this->boardSpace.push_back(vector<Position>(boardWidth)); 
   }
}

string Board::display(){
   string toReturn = "";
   for(auto& row : boardSpace){
      for(auto& cell : row){
         toReturn += cell.display() + " ";
      }
      toReturn += "\n";
   }
   return toReturn;
}

bool Board::validatePlace(int posX, int posY, Token toPlace){
   bool validMove = true;

   //check that move position is on the board
   validMove &= (posX < boardWidth && posX >= 0);
   validMove &= (posY < boardWidth && posY >= 0);

   //is the token big enough to go there?
   validMove &= (toPlace.getSize() > boardSpace[posY][posX].getSize());
   validMove &= (toPlace.getSize() <= numSizes);

   //if self consuming isn't allowed, you can't play on top of your own token
   validMove &= (selfConsume || (toPlace.getPlayer() != boardSpace[posY][posX].getPlayer()));

   return validMove;
}

bool Board::validateMove(int fromX, int fromY, int toX, int toY){
   bool validMove = true;
   //check that the from and to positions are on the board
   validMove &= (fromX < boardWidth && fromX >= 0);
   validMove &= (fromY < boardWidth && fromY >= 0);
   validMove &= (toX < boardWidth && toX >= 0);
   validMove &= (toY < boardWidth && toY >= 0);

   //check that the token being moved is larger than the token at the destination
   validMove &= (boardSpace[fromY][fromX].getSize() >
      boardSpace[toY][toX].getSize());

   //if self consuming isn't allowed, you can't move on top of your own token
   validMove &= (selfConsume || (boardSpace[fromY][fromX].getPlayer() !=
      boardSpace[toY][toX].getPlayer()));

   return validMove;
}

Token Board::getToken(int posX, int posY){
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
   boardSpace[fromY][fromX].move(&boardSpace[toY][toX]);
}

//Player
Player::Player(int idIn){
   this->id = idIn;
   for(int a = 1; a <= numSizes ; a++){
      vector <Token> toAdd;
      for(int b = 0; b < sizeCopies; b++){
         Token Focus(a,this->id);
         toAdd.push_back(Focus);
      }
      this->myTokens.push_back(toAdd);
   }
}

string Player::display(){
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

bool Player::hasToken(int tokenSize){
   bool toReturn = false;
   if(tokenSize > 0 && tokenSize <= numSizes){
      //tokens range from size 1 to numSize
      //indices start at 0, so subtract 1
      toReturn = !myTokens[tokenSize -1].empty();
   }
   return toReturn;
}

Token Player::playToken(int tokenSize){
   Token toReturn;
   if(hasToken(tokenSize)){
      toReturn = myTokens[tokenSize-1].back();
      myTokens[tokenSize-1].pop_back();
   }
   return toReturn;
}

//Position
Position::Position(){
   this->myTokens.push_back(Token(0, nullPlayer));
}

int Position::getSize(){
   Token topToken = myTokens.back();
   return topToken.getSize();
}

int Position::getPlayer(){
   Token topToken = myTokens.back();
   return topToken.getPlayer();
}

void Position::place(Token toPlace){
   myTokens.push_back(toPlace);
}

void Position::move(Position *destination){
   destination->place(myTokens.back());
   myTokens.pop_back();
}

string Position::display(){
   Token topToken = myTokens.back();
   return topToken.display();
}

//Token
Token::Token(){
   Token(0,nullPlayer);
}
Token::Token(int sizeIn, int playerIn){
   this->size = sizeIn;
   this->playerID = playerIn;
}

string Token::display(){
   string toReturn = "";
   if(playerID == nullPlayer){
      toReturn = "./.";
   }else{
      toReturn = to_string(size) + "/" + to_string(playerID);
   }
   return toReturn;
}

int Token::getSize(){
   return size;
}

int Token::getPlayer(){
   return playerID;
}
