#include "test.h"
#include <iostream>
#include <assert.h>


using namespace std;

void Test::allTests(){
   Test myTest;
   myTest.gameStart();
   cout<<"All tests passed! :D\n";
}

void Test::gameStart(){
   GameBoard toTest;
   assert(toTest.turnTracker == 1);
   int temp = 0;
   for (auto& Focus : toTest.myPlayers){
      assert(Focus.id == temp + 1);
      temp++;
   }
   //assert(toTest.checkGameEnd() == 0);
   cout<<"Game start check passed\n";
}

//test functions
