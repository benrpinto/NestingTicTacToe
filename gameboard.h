#pragma once
#include<vector>
#include<string>

//game variables
constexpr int numPlayers = 2;
constexpr int boardWidth = 3;
constexpr int numSizes = 3;
constexpr int sizeCopies = 2;
constexpr bool selfConsume = false;

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
   public:
   GameBoard();   
   int turnTracker;
   int winner;
   vector<vector<Position>> boardSpace;
   vector<Player> myPlayers;

   string display();
   int progressGame();
   bool validateMove(int posX, int posY, int tokenSize);

//   string requestMove();

//   void updateBoard();
//   int checkGameEnd();
//   possible states include in progress, won by each player, tie
   //undo move function
};

class Player{
   public:
   vector<vector<Token>> myTokens;
   int id;
//   std::string makeMove();
   //update token function
   //std::string name
   Player(int idIn);
   string display();
   bool hasToken(int tokenSize);
   Token playToken(int tokenSize);
};


class Token{
   public:
   int size;
   int playerID;
   Token();
   Token(int sizeIn, int playerIn);
   int getSize();
   int getPlayer();
   string display();
};


class Position{
   public:
   Position();
   int getSize();
   int getPlayer();
   void place(Token toPlace);
   Token myToken;
//   String display();
//   void updatePosition;
};
