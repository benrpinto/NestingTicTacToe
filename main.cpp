#include <iostream>
#include "gameboard.h"
#include "test.h"

constexpr bool runTests = true;

using namespace std;

int main(int argc, char** argv){
   cout<<"Welcome to Nesting Tic Tac Toe\n";
   if(runTests){
      cout<<"Running tests\n";
      Test myTest;
      myTest.allTests();
   }
   GameBoard myGame;
   cout<<myGame.display();
   myGame.progressGame();
   cout<<"\n\n"<<myGame.display();
   return 0;
}
