#include "test.h"
#include <iostream>
#include <assert.h>


using namespace std;

int main(){
   Test myTests;
   myTests.allTests();
   return 0;
}

void Test::allTests(){
   Test myTest;
   myTest.gameStart();
   myTest.VM1();
   myTest.VP1();
   cout<<"All tests passed! :D\n";
}

void Test::gameStart(){
   GameBoard toTest;
   assert(toTest.checkGameEnd() == inProgress);
   cout<<"Game start check passed\n";
}

//Validate Move Test 1
void Test::VM1(){
   GameBoard toTest;
   //at start of game, no moves are possible
   //because no tokens are on the board
   for(int a = 0; a < boardWidth; a++){
      for(int b = 0; b < boardWidth; b++){
         for(int c = 0; c < boardWidth; c++){
            for(int d = 0; d < boardWidth; d++){
               assert(toTest.validateMove(a,b,c,d) == false);
            }
         }
      }
   }
   cout<<"VM1 check passed\n";
}

void Test::VP1(){
   GameBoard toTest;
   //at the start of the game every position is valid to place on
   //since nothing is occupied, and no tokens are exhausted
   //but can't place 0 sized tokens
   for(int a = 0; a < boardWidth; a++){
      for(int b = 0; b < boardWidth; b++){
         assert(toTest.validatePlace(a,b,0) == false);
         for(int c = 1; c <= numSizes; c++){
            assert(toTest.validatePlace(a,b,c));
         }
      }
   }
   cout<<"VP1 check passed\n";
}

//test functions
