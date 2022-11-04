#include <iostream>
#include "gameboard.h"

using namespace std;

int main(int argc, char** argv){
   cout<<"Welcome to Nesting Tic Tac Toe\n";
   GameBoard myGame;
   cout<<myGame.display();
   
   return 0;
}
