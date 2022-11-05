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
   assert(toTest.turnTracker == 0);
   int temp = 0;
   for (auto& Focus : toTest.myPlayers){
      assert(Focus.id == temp);
      temp++;
   }
   //assert(toTest.checkGameEnd() == inProgress);
   cout<<"Game start check passed\n";
}

//test functions
