#include <iostream>
#include "Gobblet_Gobblers/gg_game.h"

constexpr bool runTests = true;

using namespace std;

int main(int argc, char** argv){
   int winner = nullPlayer;
   bool validMove;
   cout<<"Welcome to Nesting Tic Tac Toe\n";
   GGGame myGame;
   cout<<myGame.display();
   while(winner == nullPlayer){
      pair<bool, int> result = myGame.progressGame();
      validMove = result.first;
      winner = result.second;
      if(validMove){
         cout<<myGame.display();
      }
   }
   cout<<"Player "<<winner<<" wins!\n";
   return 0;
}
