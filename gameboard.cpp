#include "gameboard.h"
#include <iostream>

using namespace std;
//GameBoard
GameBoard::GameBoard(){

   this->turnTracker = 0;
   this->winner = nullPlayer;
   for(int a = 0; a < boardWidth; a++ ){
      this->boardSpace.push_back(vector<Position>(boardWidth)); 
   }
   for(int a = 0; a < numPlayers; a++){
      this->myPlayers.push_back(Player(a));
   }
}

string GameBoard::display(){
   string toReturn = "";
   for(auto& focusPlayer : myPlayers){
      toReturn += focusPlayer.display();
   }
   for(auto& row : boardSpace){
      for(auto& cell : row){
         toReturn += cell.display() + " ";
      }
      toReturn += "\n";
   }
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
               boardSpace[posY][posX].place(toPlay);
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
            boardSpace[fromY][fromX].move(&boardSpace[toY][toX]);
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
   //check that the from and to positions are on the board
   validMove &= (fromX < boardWidth && fromX >= 0);
   validMove &= (fromY < boardWidth && fromY >= 0);
   validMove &= (toX < boardWidth && toX >= 0);
   validMove &= (toY < boardWidth && toY >= 0);

   //check that the player owns the token being moved
   validMove &= (boardSpace[fromY][fromX].getPlayer() == turnTracker);

   //check that the token being moved is larger than the token at the destination
   validMove &= (boardSpace[fromY][fromX].getSize() >
      boardSpace[toY][toX].getSize());

   //if self consuming isn't allowed, you can't move on top of your own token
   validMove &= (selfConsume || (boardSpace[fromY][fromX].getPlayer() !=
      boardSpace[toY][toX].getPlayer()));

   return validMove;
}

bool GameBoard::validatePlace(int posX, int posY, int tokenSize){
   bool validMove = true;
   int existingSize = 0;
   int existingControl = nullPlayer;

   //check that move position is on the board
   validMove &= (posX < boardWidth && posX >= 0);
   validMove &= (posY < boardWidth && posY >= 0);
   //check what's in the position
   if(validMove){
      existingSize = boardSpace[posY][posX].getSize();
      existingControl = boardSpace[posY][posX].getPlayer();
   }
   //is the token big enough to go there?
   validMove &= (tokenSize <= numSizes && tokenSize > existingSize);
   //if self consuming isn't allowed, you can't play on top of your own token
   validMove &= (turnTracker != existingControl || selfConsume);
   //you can only play tokens you have
   validMove &= myPlayers[turnTracker].hasToken(tokenSize);

   return validMove;
}

int GameBoard::checkGameEnd(){
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
   //TODO: add input validation
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
