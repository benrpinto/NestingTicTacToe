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

class Board;
class Player;
class Token;
class Position;
class GameBoard;

using namespace std;

class Board{
   private:
      vector<vector<Position>> boardSpace;

   public:
      Board();
      string display() const;
      bool validateMove(int fromX, int fromY, int toX, int toY) const;
      bool validatePlace(int posX, int posY, Token toPlace) const;
      void place(int posX,int posY,Token toPlace);
      void move(int fromX, int fromY, int toX, int toY);
      int checkGameEnd(int currentPlayer, int victor);
      Token getToken(int posX, int posY) const;
};

class Player{
   private:
      vector<vector<Token>> myTokens;
      int id;
//      std::string name

   public:
      Player(int idIn);
      string display() const;
      bool hasToken(int tokenSize) const;
      Token playToken(int tokenSize);
};

class Token{
   private:
      const int size;
      const int playerID;

   public:
      Token();
      Token(int sizeIn, int playerIn);
      int getSize() const;
      int getPlayer() const;
      string display() const;
};


class Position{
   private:
      vector<Token> myTokens;

   public:
      Position();
      int getSize() const;
      int getPlayer() const;
      void place(Token toPlace);
      void move(Position& destination);
      string display() const;
};


class GameBoard{
   private:
      int turnTracker;
      int winner;
      vector<Player> myPlayers;
      Board myBoard;

   public:
      int checkGameEnd();
      bool validateMove(int fromX, int fromY, int toX, int toY) const;
      bool validatePlace(int posX, int posY, int tokenSize) const;

      GameBoard();   
      string display() const;
      pair <bool,int> progressGame();

   //undo move function
};
