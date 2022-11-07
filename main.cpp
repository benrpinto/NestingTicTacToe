#include <iostream>
#include "gameboard.h"

constexpr bool runTests = true;

using namespace std;

int main(int argc, char** argv){
   int winner = nullPlayer;
   cout<<"Welcome to Nesting Tic Tac Toe\n";
   GameBoard myGame;
   cout<<myGame.display();
   while(winner == nullPlayer){
      winner = myGame.progressGame();
      cout<<myGame.display();
   }
   cout<<"Player "<<winner<<" wins!\n";
   return 0;
}
