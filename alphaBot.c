#include <cstdlib>
#include <iostream>
#include <ctime>
#include "alphaBot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

alphaBot::alphaBot()
{
  playerNum = 1;
}

alphaBot::alphaBot(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

int alphaBot::getPlayerNum()
{
  return playerNum;
}

void alphaBot::setPlayerNum(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

Move alphaBot::chooseMove(Board thisBoard){  
  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  if(whoseTurn*playerNum <= 0) {
    Move invalid;
    return invalid;
  }

  thisBoard.print();
  cout << endl;

  Move userMove;
  vector<Move> allLegal  = thisBoard.getAllLegalMoves(playerNum);
  vector<Move> allLegalA = thisBoard.getAllLegalMoves(playerNum);
  vector<Move>::iterator iterA;

  string white = "\033[40;45m";
  string black = "\033[40;46m";
  string reset = "\033[m";

  if (playerNum > 0)
    cout << white << "WHITE";
  else
    cout << black << "BLACK";

  cout << reset << " is thinking... " << endl;

  if (playerNum > 0)
    cout << white << "WHITE";
  else
    cout << black << "BLACK";

  cout << reset << " chooses to move: ";
  /*******************************/

  for(iterA = allLegalA.begin(); iterA != allLegalA.end(); iterA++) {
 
    Board testBoardA = thisBoard.testMove(*iterA, playerNum);
    if(testBoardA.hasWon(playerNum))
      userMove = *iterA;
    
/*     vector<Move> allLegalB = testBoardA.getAllLegalMoves(opponent); */
/*     vector<Move>::iterator iterB; */
    
/*     bool badMoveB = false; */
/*     for(iterB = allLegalB.end() - 1; ((iterB >= allLegalB.begin()) && !(badMoveB)); iterB--) { */
/*       Board testBoardB = testBoardA.testMove(*iterB, opponent); */
/*       if(testBoardB.hasWon(opponent)) */
/* 	badMoveB = true; */
/*     } */
/*     if(badMoveB) */
/*       allLegalA.erase(iterA); */
  }
  if(allLegalA.size() > 0) {
    srand((unsigned)time(0));
    int kindaRandom = rand()%allLegalA.size();
    userMove = allLegalA[kindaRandom];
  } else {
    userMove = allLegal[0];
  }
      
  /*******************************/
  /*
  bool success = false;
  success = ((userMove.setOrigin(orr,oc)) && (userMove.setDestination(dr,dc)));

  if(success) {
    cout << "Successfully input move: ";
    userMove.print();
  } else {
    cout << "Failed to input move";
  }
  */

  userMove.print();
  cout << endl;

  return userMove;
}
