#pragma once
#include<vector>
#include<string>

//game variables
constexpr int numPlayers = 2;
constexpr int boardWidth = 3;
constexpr int numSizes = 3;
constexpr int sizeCopies = 2;

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
   vector<vector<Position>> boardSpace;
   vector<Player> myPlayers;

   string display();

//   int requestMove();

//   void updateBoard();
//   bool validateMove();
//   int checkGameEnd();
//   possible states include in progress, won by each player, tie
   //undo move function
};

class Player{
   public:
   vector<vector<Token>> myTokens;
   int id;
//   bool validateMove();
//   std::string makeMove();
   //update token function
   //std::string name
   Player(int idIn);
   string display();
};


class Token{
   public:
   int size;
   int playerID;
   Token();
   Token(int sizeIn, int playerIn);
   string display();
};


class Position{
   public:
   Position();
   Token myToken;
//   String display();
//   void updatePosition;
};
