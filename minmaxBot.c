#include <cstdlib>
#include <iostream>
#include <ctime>
#include "minmaxBot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

minmaxBot::minmaxBot()
{
  playerNum = 1;
}

minmaxBot::minmaxBot(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

int minmaxBot::getPlayerNum()
{
  return playerNum;
}

void minmaxBot::setPlayerNum(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

Move minmaxBot::chooseMove(Board thisBoard){  
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
/*   int searchDepth=1; */
/*   userMove = ChooseBestMove(searchDepth, &thisBoard); */

  float bestsofar = -999999.9;
  for(iterA = allLegalA.begin(); iterA != allLegalA.end(); iterA++) { 

    Board testBoardA = thisBoard.testMove(*iterA, playerNum); 
    if(testBoardA.hasWon(playerNum)) {
      userMove = *iterA; 
      break;
    }
/*     float thisScore = Evaluate(testBoardA); */
/*     if (thisScore > bestsofar) { */
/*       bestsofar = thisScore; */
/*       userMove = *iterA; */
/*     } */
      
 
    vector<Move> allLegalB = testBoardA.getAllLegalMoves(opponent);  
    vector<Move>::iterator iterB;  

    float worstsofar = 999999.9;
    for(iterB = allLegalB.begin(); iterB != allLegalB.end(); iterB++) {
      Board testBoardB = testBoardA.testMove(*iterB, opponent);  
      if(testBoardB.hasWon(opponent))
	worstsofar = -999999.9;
      float thatScore = Evaluate(testBoardB);
      if (thatScore < worstsofar) 
	worstsofar=thatScore;
    }

    if (worstsofar > bestsofar) {
      bestsofar = worstsofar;
      userMove = *iterA;
    }
  }
      

/*     bool badMoveB = false;   */
/*     for(iterB = allLegalB.end() - 1; ((iterB >= allLegalB.begin()) && !(badMoveB)); iterB--) {   */
/*       Board testBoardB = testBoardA.testMove(*iterB, opponent);   */
/*       if(testBoardB.hasWon(opponent))   */
/* 	badMoveB = true;   */
/*     }   */
/*     if(badMoveB)   */
/*       allLegalA.erase(iterA);   */
 
/*   if(allLegalA.size() > 0) {   */
/*     srand((unsigned)time(0));   */
/*     int kindaRandom = rand()%allLegalA.size();   */
/*     userMove = allLegalA[kindaRandom];   */
/*   } else {   */
/*     userMove = allLegal[0];   */
/*   }   */
      
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

float minmaxBot::Evaluate(Board thisBoard) {
  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  float evaluation = 0.0;

  // Subtract 5*|n| for every n-shell on my StartSquares
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(playerNum,iStartSquare);
    for (int x=abs(thisStartSquare.top()); x!=0; x--) {
      evaluation-=4*x;
    }    
  }
  // Add 5*|n| for every n-shell on his StartSquares
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(opponent,iStartSquare);
    for (int x=abs(thisStartSquare.top()); x!=0; x--) {
      evaluation+=4*x;
    }    
  }


  // Add 100 points for every 3 in a row (that are "row-able")
  // Add  10 points for every 2 in a row (that are "row-able")
  // Check the rows
  for (int iRow=0; iRow != 4; iRow++) {
    int nMineInThisRow = 0;
    int nHisInThisRow = 0;
    for (int iCol=0; iCol != 4; iCol++) {
      Square mySquare = thisBoard.getSquare(iRow,iCol);
      if (mySquare.top()*playerNum > 0) 
	nMineInThisRow++;
      if (mySquare.top()*opponent > 0)
	nHisInThisRow++;
    }
    if (nMineInThisRow == 3) {
      evaluation+=100;
    } else if (nMineInThisRow == 2) {
      evaluation+=10;
    }
    if (nHisInThisRow == 3) {
      evaluation-=100;
    } else if (nHisInThisRow == 2) {
      evaluation-=10;
    }
  }
    
  // Check the cols
  for (int iCol=0; iCol != 4; iCol++) {
    int nMineInThisCol = 0;
    int nHisInThisCol = 0;
    for (int iRow=0; iRow != 4; iRow++) {
      Square mySquare = thisBoard.getSquare(iRow,iCol);
      if (mySquare.top()*playerNum > 0) 
	nMineInThisCol++;
      if (mySquare.top()*opponent > 0)
	nHisInThisCol++;
    }
    if (nMineInThisCol == 3) {
      evaluation+=100;
    } else if (nMineInThisCol == 2) {
      evaluation+=10;
    }
    if (nHisInThisCol == 3) {
      evaluation-=100;
    } else if (nHisInThisCol == 2) {
      evaluation-=10;
    }
  }

  // Check the diagonals
  for (int iDiag=0; iDiag != 2; iDiag++) {
    int iRow, iCol;
    int nMineInThisDiag = 0;
    int nHisInThisDiag = 0;
    for (int iCounter=0; iCounter != 4; iCounter++) {
      switch (iDiag) 
	{
	case 0 : iRow=iCounter; iCol=iCounter; break;
	case 1 : iRow=iCounter; iCol=4-iCounter; break;
	default : break;
	}
      Square mySquare = thisBoard.getSquare(iRow,iCol);
      if (mySquare.top()*playerNum > 0) 
	nMineInThisDiag++;
      if (mySquare.top()*opponent > 0)
	nHisInThisDiag++;
    }
    if (nMineInThisDiag == 3) {
      evaluation+=100;
    } else if (nMineInThisDiag == 2) {
      evaluation+=10;
    }
    if (nHisInThisDiag == 3) {
      evaluation-=100;
    } else if (nHisInThisDiag == 2) {
      evaluation-=10;
    }
  }


  // Subtract one point for each of your pieces that are covered
  // Add one point for each of his pieces that are covered
  for (int iRow=0; iRow!=4; iRow++) {
    for (int iCol=0; iCol!=4; iCol++) {
      Square iSquare = thisBoard.getSquare(iRow,iCol); 
      vector<int> iStack = iSquare.getmyStack();
      for (vector<int>::iterator it = iStack.begin(); 
	   it < iStack.end()-1;
	   it++) {
	if ((*it)*playerNum > 0) {
	  evaluation-=1;
	} 
	if ((*it)*playerNum < 0) {
	  evaluation+=1;
	}
      }
    }
  }

  return evaluation;
}

/* Move minimaxBot::ChooseBestMove(int searchDepth, Board *thisBoard) { */
/*   float positionValue = -9999999.0; */

/*   vector<Move> allLegal = thisBoard->getAllLegalMoves(playerNum); */
/*   Move favoriteMove = allLegal[0]; */
/*   for (vector<Move>::iterator it = allLegal->begin();  */
/*        it != allLegal->end(); */
/*        it++) { */
/*     if (searchDepth <= 0) { */
      
/*     Board *thisTestBoard = new Board(thisBoard->testMove(*it)); */
    

/*     float thisAB=AlphaBeta(*it,searchDepth,thisBoard,alpha,beta); */
/*     if (thisAB > alpha) { */
/*       alpha = thisAB; */
/*       myChoice = *it; */
/*     } */
/*   } */
/*   return myChoice; */
/* } */


/* float minimaxBot::AlphaBeta(Move thisMove, */
/* 			    int searchDepth, */
/* 			    Board *thisBoard, */
/* 			    float alpha, beta) { */
/*   if (searchDepth <= 0) { */
/*     return Evaluate(*thisBoard); */
/*   } */
/*   for ( */
/* } */
