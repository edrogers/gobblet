#include <iostream>
#include <vector>
#include <cstdlib>
#include "human.h"
#include "alphaBot.h"
#include "betaBot.h"
#include "Bot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

Move promptUser(Board thisBoard);

int main()
{
  Board myBoard;
  Human playerA(1);
  Bot playerB(-1);

  do {
    Move nextMove;

    if(myBoard.getWhoseTurn() == 1)
      nextMove = playerA.chooseMove(myBoard);
    else 
      nextMove = playerB.chooseMove(myBoard);

    myBoard.makeMove(nextMove, myBoard.getWhoseTurn());
  } while ( !(myBoard.hasWon(1)) && !(myBoard.hasWon(-1)) );
  
  myBoard.print();
  char* white = "\033[40;45m";
  char* black = "\033[40;46m";
  char* reset = "\033[m";

  if (myBoard.hasWon(1)) {
    cout << white << "WHITE";
  } else {
    cout << black << "BLACK";
  }
  cout << reset << " has won!" << endl;

  return -1;
}


