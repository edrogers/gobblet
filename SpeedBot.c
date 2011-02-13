#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "SpeedBot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

SpeedBot::SpeedBot()
{
  playerNum = 1;
}

SpeedBot::SpeedBot(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

int SpeedBot::getPlayerNum()
{
  return playerNum;
}

void SpeedBot::setPlayerNum(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

Move SpeedBot::chooseMove(Board thisBoard){  

  /* ofstream logfile; */
  /* logfile.open("log.txt", ios_base::app); */

  int depth = 2;

  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  if(whoseTurn*playerNum <= 0) {
    Move invalid;
    return invalid;
  }

  thisBoard.print();
  cout << endl;

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

  vector<Move> allLegal  = thisBoard.getAllLegalMoves(playerNum);

  int nPiecesOpponentMoved = 0;
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(opponent,iStartSquare);
    nPiecesOpponentMoved += 4-abs(thisStartSquare.top());
  }
  if (nPiecesOpponentMoved < 3) {
    for (vector<Move>::iterator thisMove = allLegal.begin();
	 thisMove != allLegal.end(); ) {
      if (thisMove->isOriginInPlayBoard()) {
	allLegal.erase(thisMove);
	continue;
      }
      thisMove++;
    }
    //    srand((unsigned)time(0));
    srand(0);
    int kindaRandom = rand()%allLegal.size();
    /* logfile << "Random Move to start" << endl; */
    /* logfile << (allLegal[kindaRandom]).getOriginRow() << "," << (allLegal[kindaRandom]).getOriginCol() << " -> "; */
    /* logfile << (allLegal[kindaRandom]).getDestinationRow() << "," << (allLegal[kindaRandom]).getDestinationCol() << endl; */
    /* logfile.close(); */
    return allLegal[kindaRandom];
  }


  /* logfile << "Reordering Moves" << endl; */
  /* logfile << "  Starting with " << allLegal.size() << " legal moves." << endl; */
  /* vector<Move> OrderedMoves = ReorderMoves(allLegal,thisBoard, logfile); */
  /* logfile << "  End up with " << OrderedMoves.size() << " legal moves." << endl; */

  vector<Move> OrderedMoves = ReorderMoves(allLegal,thisBoard);
  /* vector<Move> OrderedMoves = allLegal; */

  /* Move  FavoriteMoveSoFar = OrderedMoves[0]; // Just start with whatever */
  Move* FavoriteMoveSoFar = NULL;
  float FavoriteMoveSoFarScore = 0.0;

  Move* WinningMove = new Move();
  WinningMove->setOrigin(3,3);
  WinningMove->setDestination(2,0);
  
  float alpha = -999999.9;
  float beta  =  999999.9;
  for (vector<Move>::iterator testMove = OrderedMoves.begin();
       testMove != OrderedMoves.end();
       testMove++) {
    Board testBoard = thisBoard.testMove(*testMove,playerNum);
    float score = alphaBeta(testBoard, depth, alpha, beta);

    if ((*testMove) == (*WinningMove)) {
      cout << "  Winning Move Score: " << score << "  ";
      testMove->print();
      cout << endl;
    }

    if (FavoriteMoveSoFar == NULL) {
      FavoriteMoveSoFar = &(*testMove);
      FavoriteMoveSoFarScore = score;
      continue;
    }     

    if (score*playerNum > FavoriteMoveSoFarScore*playerNum) {
      FavoriteMoveSoFar = &(*testMove);
      FavoriteMoveSoFarScore = score;
    }
  }

  /* logfile << (FavoriteMoveSoFar).getOriginRow() << "," << (FavoriteMoveSoFar).getOriginCol() << " -> "; */
  /* logfile << (FavoriteMoveSoFar).getDestinationRow() << "," << (FavoriteMoveSoFar).getDestinationCol() << endl; */
  if (FavoriteMoveSoFar) 
    FavoriteMoveSoFar->print();
  cout << endl;


  cout << "  Chosen Move Score: " << FavoriteMoveSoFarScore << "  ";
  FavoriteMoveSoFar->print();
  cout << endl;

  /* logfile.close(); */
  return *FavoriteMoveSoFar;
}

float SpeedBot::Evaluate(Board thisBoard) {

  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  float evaluation = 0.0;

  // Unused piece penalty
  // Subtract 4*|n| for every n-shell on my StartSquares 
  // (add 4*|n| for every n-shell on their StartSquares)
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(playerNum,iStartSquare);
    for (int x=abs(thisStartSquare.top()); x!=0; x--) {
      evaluation-=4*x*playerNum;
    }    
  }
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(opponent,iStartSquare);
    for (int x=abs(thisStartSquare.top()); x!=0; x--) {
      evaluation-=4*x*opponent;
    }    
  }


  // Add 100 points for every 3 in a row (that are "row-able")
  // Add  10 points for every 2 in a row (that are "row-able")
  //  (Note: "row-able" == able to make a four in a row.  e.g., not the once-off-diagonal "row")
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
      evaluation+=100*playerNum;
    } else if (nMineInThisRow == 2) {
      evaluation+=10*playerNum;
    }
    if (nHisInThisRow == 3) {
      evaluation+=100*opponent;
    } else if (nHisInThisRow == 2) {
      evaluation+=10*opponent;
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
      evaluation+=100*playerNum;
    } else if (nMineInThisCol == 2) {
      evaluation+=10*playerNum;
    }
    if (nHisInThisCol == 3) {
      evaluation+=100*opponent;
    } else if (nHisInThisCol == 2) {
      evaluation+=10*opponent;
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
      evaluation+=100*playerNum;
    } else if (nMineInThisDiag == 2) {
      evaluation+=10*playerNum;
    }
    if (nHisInThisDiag == 3) {
      evaluation+=100*opponent;
    } else if (nHisInThisDiag == 2) {
      evaluation+=10*opponent;
    }
  }


  // Subtract one point for each of your pieces that are covered
  // Add one point for each of his pieces that are covered
  for (int iRow=0; iRow!=4; iRow++) {
    for (int iCol=0; iCol!=4; iCol++) {
      Square iSquare = thisBoard.getSquare(iRow,iCol); 
      vector<int> iStack = iSquare.getmyStack();
      for (vector<int>::iterator it = iStack.begin(); 
	   it != iStack.end() && it < iStack.end()-1;
	   it++) {
	if ((*it)*playerNum > 0) {
	  evaluation-=1*playerNum;
	} 
	if ((*it)*opponent > 0) {
	  evaluation-=1*opponent;
	}
      }
    }
  }

  return evaluation;
}

int SpeedBot::nOtherPiecesThisRowAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iRow = thisMove.getDestinationRow();
  int nMyOtherPiecesInThisRowAfterMove = 0;
  for (int iCol=0; iCol != 4; iCol++) {
    if (iCol != thisMove.getDestinationCol()) {
      if (!((iCol == thisMove.getOriginCol()) && (iRow == thisMove.getOriginRow()))) {
	Square mySquare = thisBoard.getSquare(iRow,iCol);
	if (mySquare.top()*PlayerToMove > 0)
	  nMyOtherPiecesInThisRowAfterMove++;
      } else {
	Square mySquare = thisBoard.getSquare(iRow,iCol);
	if (mySquare.second_from_top()*PlayerToMove > 0)
	  nMyOtherPiecesInThisRowAfterMove++;
      }
    }
  }
  return nMyOtherPiecesInThisRowAfterMove;
}

int SpeedBot::nOtherPiecesThisColAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iCol = thisMove.getDestinationCol();
  int nMyOtherPiecesInThisColAfterMove = 0;
  for (int iRow=0; iRow != 4; iRow++) {
    if (iRow != thisMove.getDestinationRow()) {
      if (!((iRow == thisMove.getOriginRow()) && (iCol == thisMove.getOriginCol()))) {
	Square mySquare = thisBoard.getSquare(iCol,iRow);
	if (mySquare.top()*PlayerToMove > 0)
	  nMyOtherPiecesInThisColAfterMove++;
      } else {
	Square mySquare = thisBoard.getSquare(iCol,iRow);
	if (mySquare.second_from_top()*PlayerToMove > 0)
	  nMyOtherPiecesInThisColAfterMove++;
      }
    }
  }
  return nMyOtherPiecesInThisColAfterMove;
}

int SpeedBot::nOtherPiecesThisDiagAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iCol = thisMove.getDestinationCol();
  int iRow = thisMove.getDestinationRow();
  int nMyOtherPiecesInThisDiagAfterMove = 0;
  if (iRow==iCol) {
    for (int iRow=0; iRow != 4; iRow++) {
      if (iRow != thisMove.getDestinationRow()) {
	iCol=iRow;
	if (!((iRow == thisMove.getOriginRow()) && (iCol == thisMove.getOriginCol()))) {
	  Square mySquare = thisBoard.getSquare(iRow,iCol);
	  if (mySquare.top()*PlayerToMove > 0)
	    nMyOtherPiecesInThisDiagAfterMove++;
	} else {
	  Square mySquare = thisBoard.getSquare(iRow,iCol);
	  if (mySquare.second_from_top()*PlayerToMove > 0)
	    nMyOtherPiecesInThisDiagAfterMove++;
	}
      }
    }
  } else if (iRow+iCol == 3) {
    for (int iRow=0; iRow != 4; iRow++) {
      if (iRow != thisMove.getDestinationRow()) {
	iCol=3-iRow;
	if (!((iRow == thisMove.getOriginRow()) && (iCol == thisMove.getOriginCol()))) {
	  Square mySquare = thisBoard.getSquare(iRow,iCol);
	  if (mySquare.top()*PlayerToMove > 0)
	    nMyOtherPiecesInThisDiagAfterMove++;
	} else {
	  Square mySquare = thisBoard.getSquare(iRow,iCol);
	  if (mySquare.second_from_top()*PlayerToMove > 0)
	    nMyOtherPiecesInThisDiagAfterMove++;
	}
      }
    }
  } else {
    return 0;
  }

  return nMyOtherPiecesInThisDiagAfterMove;
}

bool SpeedBot::isAMoveToDiag(Move thisMove) {
  if (thisMove.getDestinationRow() == thisMove.getDestinationCol())
    return true;
  if (thisMove.getDestinationRow() == 3-thisMove.getDestinationCol())
    return true;
  return false;
}

int SpeedBot::nOpponentBigPiecesThisRowAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iRow = thisMove.getDestinationRow();
  int nOpponentBigPiecesInThisRowAfterMove = 0;
  for (int iCol=0; iCol != 4; iCol++) {
    Square mySquare = thisBoard.getSquare(iRow,iCol);
    if (mySquare.top()*opponent == 4)
      nOpponentBigPiecesInThisRowAfterMove++;
  }
  return nOpponentBigPiecesInThisRowAfterMove;
}

int SpeedBot::nOpponentBigPiecesThisColAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iCol = thisMove.getDestinationCol();
  int nOpponentBigPiecesInThisColAfterMove = 0;
  for (int iRow=0; iRow != 4; iRow++) {
    Square mySquare = thisBoard.getSquare(iCol,iRow);
    if (mySquare.top()*opponent == 4)
      nOpponentBigPiecesInThisColAfterMove++;
  }
  return nOpponentBigPiecesInThisColAfterMove;
}

int SpeedBot::nOpponentBigPiecesThisDiagAfterPlayerMoves(Board thisBoard, Move thisMove) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;
  
  int iCol = thisMove.getDestinationCol();
  int iRow = thisMove.getDestinationRow();
  int nOpponentBigPiecesThisDiagAfterPlayerMoves = 0;
  if (iRow==iCol) {
    for (int iRow=0; iRow != 4; iRow++) {
      if (iRow != thisMove.getDestinationRow()) {
	iCol=iRow;
	Square mySquare = thisBoard.getSquare(iCol,iRow);
	if (mySquare.top()*opponent == 4)
	  nOpponentBigPiecesThisDiagAfterPlayerMoves++;
      }
    }
  } else if (iRow+iCol == 3) {
    for (int iRow=0; iRow != 4; iRow++) {
      if (iRow != thisMove.getDestinationRow()) {
	iCol=3-iRow;
	Square mySquare = thisBoard.getSquare(iCol,iRow);
	if (mySquare.top()*opponent == 4)
	  nOpponentBigPiecesThisDiagAfterPlayerMoves++;
      }
    }
  } else {
    return 0;
  }

  return nOpponentBigPiecesThisDiagAfterPlayerMoves;
}

vector<Move> SpeedBot::ReorderMoves(vector<Move> ListOfMoves, Board thisBoard) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int opponent = -1*PlayerToMove;

  vector<Move> ThreeInARow;                              
  vector<Move> UnobstructedThreeInARow;			 
  vector<Move> DoubleUnobstructedThreeInARow;		 
  vector<Move> BigManLinksDoubleUnobstructedThreeInARow; 
  vector<Move> NoneOfTheAbove;
  vector<Move> CompleteListReordered;

  // Loop through every move:
  for (vector<Move>::iterator thisMove = ListOfMoves.begin();
	 thisMove != ListOfMoves.end(); ) {

    bool isAtLeastThreeInARow                              = false;                             
    bool isAtLeastUnobstructedThreeInARow                  = false;                 
    bool UnobstructedInRow                                 = false;                                
    bool UnobstructedInCol                                 = false;                                
    bool UnobstructedInDiag                                = false;                               
    bool isAtLeastDoubleUnobstructedThreeInARow            = false;           
    bool isAtLeastBigManLinksDoubleUnobstructedThreeInARow = false;

    // check the row
    if (nOtherPiecesThisRowAfterPlayerMoves(thisBoard, *thisMove) > 2) {
      isAtLeastThreeInARow |= true;
      // Is it unobstructed?
      UnobstructedInRow = (nOpponentBigPiecesThisRowAfterPlayerMoves(thisBoard, *thisMove) == 0);
      if (UnobstructedInRow) {
	isAtLeastUnobstructedThreeInARow |= true;
      }
    }
    // check the col
    if (nOtherPiecesThisColAfterPlayerMoves(thisBoard, *thisMove) > 2) {
      isAtLeastThreeInARow |= true;
      // Is it unobstructed?
      UnobstructedInCol = (nOpponentBigPiecesThisColAfterPlayerMoves(thisBoard, *thisMove) == 0);
      if (UnobstructedInCol) {
	isAtLeastUnobstructedThreeInARow |= true;
      }
    }
    // check the diag
    if (nOtherPiecesThisDiagAfterPlayerMoves(thisBoard, *thisMove) > 2) {
      isAtLeastThreeInARow |= true;
      // Is it unobstructed?
      UnobstructedInDiag = (nOpponentBigPiecesThisDiagAfterPlayerMoves(thisBoard, *thisMove) == 0);
      if (UnobstructedInDiag) {
	isAtLeastUnobstructedThreeInARow |= true;
      }
    }

    int nTimesUnobstructedThreeInARow = 0;
    if (UnobstructedInRow)  nTimesUnobstructedThreeInARow++;
    if (UnobstructedInCol)  nTimesUnobstructedThreeInARow++;
    if (UnobstructedInDiag) nTimesUnobstructedThreeInARow++;
    if (nTimesUnobstructedThreeInARow > 1) {
      isAtLeastDoubleUnobstructedThreeInARow = true;
    }
    
    Square mySquare = thisBoard.getSquare(thisMove->getOriginRow(), thisMove->getOriginCol());
    int sizeOfMovedPiece = mySquare.top()*PlayerToMove;

    if (isAtLeastDoubleUnobstructedThreeInARow && (sizeOfMovedPiece == 4)) {
      isAtLeastBigManLinksDoubleUnobstructedThreeInARow = true;
    }
    
    if (isAtLeastBigManLinksDoubleUnobstructedThreeInARow) {
      BigManLinksDoubleUnobstructedThreeInARow.push_back(*thisMove);
      ListOfMoves.erase(thisMove);
      continue;
    } else if (isAtLeastDoubleUnobstructedThreeInARow) {
      DoubleUnobstructedThreeInARow.push_back(*thisMove);
      ListOfMoves.erase(thisMove);
      continue;
    } else if (isAtLeastUnobstructedThreeInARow) {
      UnobstructedThreeInARow.push_back(*thisMove);
      ListOfMoves.erase(thisMove);
      continue;
    } else if (isAtLeastThreeInARow) {
      ThreeInARow.push_back(*thisMove);
      ListOfMoves.erase(thisMove);
      continue;
    } else {
      NoneOfTheAbove.push_back(*thisMove);
      ListOfMoves.erase(thisMove);
      continue;
    }

  }
      
  CompleteListReordered.insert(CompleteListReordered.end(),
			       BigManLinksDoubleUnobstructedThreeInARow.begin(),
			       BigManLinksDoubleUnobstructedThreeInARow.end());
  CompleteListReordered.insert(CompleteListReordered.end(),
			       DoubleUnobstructedThreeInARow.begin(),
			       DoubleUnobstructedThreeInARow.end());
  CompleteListReordered.insert(CompleteListReordered.end(),
			       UnobstructedThreeInARow.begin(),
			       UnobstructedThreeInARow.end());
  CompleteListReordered.insert(CompleteListReordered.end(),
			       ThreeInARow.begin(),
			       ThreeInARow.end());
  CompleteListReordered.insert(CompleteListReordered.end(),
			       NoneOfTheAbove.begin(),
			       NoneOfTheAbove.end());

  return CompleteListReordered;
}

float SpeedBot::alphaBeta(Board thisBoard, int depth, float alpha, float beta) {
  int PlayerToMove = thisBoard.getWhoseTurn();
  int Opponent     = PlayerToMove*-1;

  if (thisBoard.hasWon(PlayerToMove)) {
    return PlayerToMove*999999.9;
  }
  if (thisBoard.hasWon(Opponent)) {
    return Opponent*999999.9;
  }
  if (depth <= 0) {
    return Evaluate(thisBoard);
  }
  vector<Move> LegalMoves = thisBoard.getAllLegalMoves(PlayerToMove);

  vector<Move> OrderedMoves = ReorderMoves(LegalMoves,thisBoard);
  /* vector<Move> OrderedMoves = LegalMoves; */
  if (PlayerToMove > 0) {
    for (vector<Move>::iterator testMove = OrderedMoves.begin();
	 testMove != OrderedMoves.end();
	 testMove++) {
      Board testBoard = thisBoard.testMove(*testMove,PlayerToMove);
      float score = alphaBeta(testBoard,depth-1,alpha,beta);
      if (score > alpha) {
	alpha = score;
      }
      if (alpha >= beta) {
	return alpha;
      }
    }
    return alpha;
  }
  if (PlayerToMove < 0) {
    for (vector<Move>::iterator testMove = OrderedMoves.begin();
	 testMove != OrderedMoves.end();
	 testMove++) {
      Board testBoard = thisBoard.testMove(*testMove,PlayerToMove);
      float score = alphaBeta(testBoard,depth-1,alpha,beta);
      if (score < beta) {
	beta = score;
      }
      if (alpha >= beta) {
	return beta;
      }
    }
    return beta;
  }
}
