#pragma once
#include<vector>
#include<string>

//game variables
constexpr int numPlayers = 2;
constexpr int boardWidth = 3;
constexpr int numSizes = 3;
constexpr int sizeCopies = 2;
constexpr bool selfConsume = true;
constexpr bool placeOnly = false;

//signalling constants
constexpr int nullPlayer = -1;
constexpr int inProgress = -1;
constexpr int tieGame = -2;

class GameBoard;
class Player;
class Token;
class Position;

using namespace std;

class GameBoard{
   private:
      int turnTracker;
      int winner;
      vector<vector<Position>> boardSpace;
      vector<Player> myPlayers;
      int checkGameEnd();

   public:
      GameBoard();   
      string display();
      int progressGame();
      bool validateMove(int posX, int posY, int tokenSize);

   //undo move function
};

class Player{
   private:
      vector<vector<Token>> myTokens;
      int id;
//      std::string name

   public:
      Player(int idIn);
      string display();
      bool hasToken(int tokenSize);
      Token playToken(int tokenSize);
};


class Token{
   private:
      int size;
      int playerID;

   public:
      Token();
      Token(int sizeIn, int playerIn);
      int getSize();
      int getPlayer();
      string display();
};


class Position{
   private:
      vector<Token> myTokens;

   public:
      Position();
      int getSize();
      int getPlayer();
      void place(Token toPlace);
      void move(Position destination);
      string display();
//      void updatePosition;
};
