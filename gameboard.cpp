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
         toReturn += cell.myToken.display() + " ";
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
      cin>>input;
      if(input == "q"){
         //quitting is always a valid mov
         validMove = true;
         //will have to change to accommodate for more than 2 players
         winner = (turnTracker + 1) % numPlayers;
      }else{
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
         }else{
            cout<<"Invalid Move\n";
	 }
      }
   }
   turnTracker = (turnTracker + 1) % numPlayers;
   //TODO change to be the result of checkGameEnd
   return turnTracker;
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
   validMove &= (tokenSize < numSizes && tokenSize > existingSize);
//   cout<<"size check:"<<to_string(validMove)<<"\n";
   //if self consuming isn't allowed, you can't play on top of your own token
   validMove &= (turnTracker != existingControl || selfConsume);
//   cout<<"self consume check:"<<to_string(validMove)<<"\n";
   //you can only play tokens you have
   validMove &= myPlayers[turnTracker].hasToken(tokenSize);
//   cout<<"hasToken check:"<<to_string(validMove)<<"\n";

   return validMove;
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
   this->myToken = Token(0, nullPlayer);
}

int Position::getSize(){
   return myToken.getSize();
}

int Position::getPlayer(){
   return myToken.getPlayer();
}

void Position::place(Token toPlace){
   myToken = toPlace;
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
