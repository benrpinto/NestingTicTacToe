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
   int tokenSize;
   bool validMove = false;

   while(!validMove){
      getline(cin,input);
//      cout<<to_string(input.length())<<"\n";
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
//         cout<<posX<<":"<<posY<<":"<<tokenSize<<"\n";
         validMove = validateMove(posX, posY, tokenSize);
         if(validMove){
            Token toPlay = myPlayers[turnTracker].playToken(tokenSize);
            if(toPlay.getPlayer() != nullPlayer){
               boardSpace[posY][posX].place(toPlay);
            }
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

bool GameBoard::validateMove(int posX, int posY, int tokenSize){
   bool validMove = true;
   int existingSize = 0;
   int existingControl = nullPlayer;

   //check that move position is on the board
   validMove &= (posX < boardWidth && posX >= 0);
   validMove &= (posY < boardWidth && posY >= 0);
//   cout<<"position check:"<<to_string(validMove)<<"\n";
   //check what's in the position
   if(validMove){
      existingSize = boardSpace[posY][posX].getSize();
      existingControl = boardSpace[posY][posX].getPlayer();
//      cout<<"existing position "<<existingSize<<"/"<<existingControl<<"\n";
   }
   //is the token big enough to go there?
   validMove &= (tokenSize <= numSizes && tokenSize > existingSize);
//   cout<<"size check:"<<to_string(validMove)<<"\n";
   //if self consuming isn't allowed, you can't play on top of your own token
   validMove &= (turnTracker != existingControl || selfConsume);
//   cout<<"self consume check:"<<to_string(validMove)<<"\n";
   //you can only play tokens you have
   validMove &= myPlayers[turnTracker].hasToken(tokenSize);
//   cout<<"hasToken check:"<<to_string(validMove)<<"\n";

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

void Position::move(Position destination){
   Token toMove;
   toMove = myTokens.back();
   destination.place(toMove);
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
