#include <iostream>
#include <vector>
#include <cstdlib>
#include "human.h"
#include "PhpBot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

int main(int argc, char* argv[])
{
  string boardSquareState[4][4];
  string whiteStartSquareState[3];
  string blackStartSquareState[3];
  for (int iRow = 0; iRow != 6; iRow++) {
    if (iRow < 4) { 
      for (int iCol = 0; iCol != 4; iCol++) {
	boardSquareState[iRow][iCol] = argv[iRow*4+iCol+1];
      }
    } else if (iRow == 4) {
      for (int iCol = 0; iCol != 3; iCol++) {
	whiteStartSquareState[iCol] = argv[17+iCol];
      }
    } else if (iRow == 5) {
      for (int iCol = 0; iCol != 3; iCol++) {
	blackStartSquareState[iCol] = argv[20+iCol];
      }
    }
  }
  string moveOrig(argv[23]);
  string moveDest(argv[24]);

  Board myBoard(boardSquareState, whiteStartSquareState, blackStartSquareState);
  Move thisMove(moveOrig,moveDest);

  bool madeMove = false;
  madeMove = myBoard.makeMove(thisMove, myBoard.getWhoseTurn());

  if (madeMove) {
    PhpBot playerB(-1);
    Move nextMove = playerB.chooseMove(myBoard);
    myBoard.makeMove(nextMove, myBoard.getWhoseTurn());
  }  

  myBoard.php_print();

  return 0;
}


