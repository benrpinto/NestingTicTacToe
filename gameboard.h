#include<vector>
#include<string>

constexpr int numPlayers = 2;
constexpr int boardWidth = 3;

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
//   void updateBoard();
//   bool validateMove();
//   int checkGameEnd();
   //undo move function
};

class Player{
   public:
//   vector<vector<Token>> myTokens;
   int id;
//0 is null player
//   bool validateMove();
//   std::string makeMove();
   //update token function
   //std::string name
   Player(int idIn);
};


class Token{
   public:
   int size;
   int playerID;
   //Position
   Token();
   Token(int sizeIn, int playerIn);
};


class Position{
   public:
   Position();
   Token myToken;
//   void updatePosition;
};
