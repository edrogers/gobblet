#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Bot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

Bot::Bot()
{
  playerNum = 1;
}

Bot::Bot(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

int Bot::getPlayerNum()
{
  return playerNum;
}

void Bot::setPlayerNum(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

Move Bot::chooseMove(Board thisBoard){  

  /* ofstream logfile; */
  /* logfile.open("log.txt", ios_base::app); */

  int depth = 1;

  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  if(whoseTurn*playerNum <= 0) {
    Move invalid;
    return invalid;
  }

  thisBoard.print();
  cout << endl;

  char* white = "\033[40;45m";
  char* black = "\033[40;46m";
  char* reset = "\033[m";

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

  int nPiecesMoved = 0;
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(playerNum,iStartSquare);
    nPiecesMoved += 4-abs(thisStartSquare.top());
  }
  if (nPiecesMoved <= 3) {
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

  Move FavoriteMoveSoFar = OrderedMoves[0]; // Just start with whatever
  
  float alpha = -999999.9;
  float beta  =  999999.9;
  for (vector<Move>::iterator testMove = OrderedMoves.begin();
       testMove != OrderedMoves.end();
       testMove++) {
    Board testBoard = thisBoard.testMove(*testMove,playerNum);
    float score = alphaBeta(testBoard, depth-1, alpha, beta);
    if (score > alpha) {
      alpha = score;
      FavoriteMoveSoFar = *testMove;
    }
    if (score >= beta) {
      FavoriteMoveSoFar = *testMove;
      break;
    }
  }

  /* logfile << (FavoriteMoveSoFar).getOriginRow() << "," << (FavoriteMoveSoFar).getOriginCol() << " -> "; */
  /* logfile << (FavoriteMoveSoFar).getDestinationRow() << "," << (FavoriteMoveSoFar).getDestinationCol() << endl; */
  FavoriteMoveSoFar.print();
  cout << endl;

  /* logfile.close(); */
  return FavoriteMoveSoFar;
}

float Bot::Evaluate(Board thisBoard) {

  int whoseTurn = thisBoard.getWhoseTurn();
  int opponent = (-1)*playerNum;

  float evaluation = 0.0;

  // Subtract 4*|n| for every n-shell on my StartSquares
  for (int iStartSquare=0; iStartSquare!=3; iStartSquare++) {
    Square thisStartSquare = thisBoard.getStartSquare(playerNum,iStartSquare);
    for (int x=abs(thisStartSquare.top()); x!=0; x--) {
      evaluation-=4*x;
    }    
  }
  // Add 4*|n| for every n-shell on his StartSquares
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
	   it != iStack.end() && it < iStack.end()-1;
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

vector<Move> Bot::ReorderMoves(vector<Move> ListOfMoves, Board thisBoard, ofstream& logfile) {
  int PlayerToMove = thisBoard.getWhoseTurn();

/*   // Start of game, skip all this reordering */
/*   int NMyPiecesOnBoard = 0; */
/*   for (int iRow=0; iRow != 4; iRow++) { */
/*     for (int iCol=0; iCol != 4; iCol++) { */
/*       Square thisSquare = thisBoard.getSquare(iRow,iCol); */
/*       if (thisSquare.top()*PlayerToMove > 0) */
/* 	NMyPiecesOnBoard++; */
/*     } */
/*   } */
/*   if (NMyPiecesOnBoard < 3)  */
/*     return ListOfMoves; */


/*   vector<Move> OrderedList; */

  vector<Move> BigList;
  vector<Move> DiagBigList;
  vector<Move> NoSelfDiagBigList;

  logfile << "      During reordering: ListOfMoves has " << ListOfMoves.size() << " legal moves." << endl;

  // First (and least important) tweak, the bigger pieces the better
  for (int pieceSize=4; pieceSize > 0; pieceSize--) {
    for (vector<Move>::iterator thisMove = ListOfMoves.begin();
	 thisMove != ListOfMoves.end(); ) {
      int OriginRow = thisMove->getOriginRow();
      int OriginCol = thisMove->getOriginCol();
      Square thisSquare = thisBoard.getSquare(OriginRow,OriginCol);
      if (abs(thisSquare.top()) == pieceSize) {
	BigList.push_back(*thisMove);
	ListOfMoves.erase(thisMove);
	continue;
      }
      thisMove++;
    }
  }

  logfile << "      During reordering: BigList has " << BigList.size() << " legal moves." << endl;

  // Check moves to squares on diagonals before others
  for (vector<Move>::iterator thisMove = BigList.begin();
       thisMove != BigList.end(); ) {
    int DestinationRow = thisMove->getDestinationRow();
    int DestinationCol = thisMove->getDestinationCol();
    if ( (DestinationRow==DestinationCol) ||
	 (DestinationRow+DestinationCol==3) ) {
      DiagBigList.push_back(*thisMove);
      BigList.erase(thisMove);
      continue;
    }
    thisMove++;
  }
  for (vector<Move>::iterator thisMove = BigList.begin();
       thisMove != BigList.end(); ) {
    DiagBigList.push_back(*thisMove);
    BigList.erase(thisMove);
  }

  logfile << "      During reordering: DiagBigList has " << DiagBigList.size() << " legal moves." << endl;

  // Highest priority.  Examine moves that gobble your own LAST
  for (vector<Move>::iterator thisMove = DiagBigList.begin();
       thisMove != DiagBigList.end(); ) {
    int DestinationRow = thisMove->getDestinationRow();
    int DestinationCol = thisMove->getDestinationCol();
    Square thisSquare = thisBoard.getSquare(DestinationRow,DestinationCol);
    if (thisSquare.top()*PlayerToMove <= 0) {
      NoSelfDiagBigList.push_back(*thisMove);
      DiagBigList.erase(thisMove);
      continue;
    }
    thisMove++;
  }
  for (vector<Move>::iterator thisMove = DiagBigList.begin();
       thisMove != DiagBigList.end(); ) {
    NoSelfDiagBigList.push_back(*thisMove);
    DiagBigList.erase(thisMove);
  }

  logfile << "      During reordering: NoSelfDiagBigList has " << NoSelfDiagBigList.size() << " legal moves." << endl;

  return NoSelfDiagBigList;

  // LATER TEST

/*   vector<Move> ListOfMovesWithThreeInARows[21]; */
/*   // Order by three-in-a-rows resulting */
/*   for (vector<Move>::iterator thisMove = ListOfMoves.begin(); */
/*        thisMove != ListOfMoves.end(); thisMove++) { */
/*     int NThreeInARows = 0; */
/*     // Compute the number of 3-in-a-rows for this move */
/*     Board testBoard = thisBoard.testMove(*thisMove,thisBoard.getWhoseTurn()); */

/*     // Check the rows */
/*     for (int iRow=0; iRow != 4; iRow++) { */
/*       int nMineInThisRow = 0; */
/*       int nHisInThisRow = 0; */
/*       for (int iCol=0; iCol != 4; iCol++) { */
/* 	Square mySquare = testBoard.getSquare(iRow,iCol); */
/* 	if (mySquare.top()*PlayerToMove > 0)  */
/* 	  nMineInThisRow++; */
/* 	if (mySquare.top()*PlayerToMove < 0) */
/* 	  nHisInThisRow++; */
/*       } */
/*       if (nMineInThisRow == 3) { */
/* 	NThreeInARows++; */
/*       } */
/*       if (nHisInThisRow == 3) { */
/* 	NThreeInARows--; */
/*       } */
/*     } */

/*     // Check the cols */
/*     for (int iCol=0; iCol != 4; iCol++) { */
/*       int nMineInThisCol = 0; */
/*       int nHisInThisCol = 0; */
/*       for (int iRow=0; iRow != 4; iRow++) { */
/* 	Square mySquare = testBoard.getSquare(iRow,iCol); */
/* 	if (mySquare.top()*PlayerToMove > 0) */
/* 	  nMineInThisCol++; */
/* 	if (mySquare.top()*PlayerToMove < 0) */
/* 	  nMineInThisCol--; */
/*       } */
/*       if (nMineInThisCol == 3) { */
/* 	NThreeInARows++; */
/*       } */
/*       if (nHisInThisCol == 3) { */
/* 	NThreeInARows--; */
/*       } */
/*     } */

/*     // Check the diagonals */
/*     for (int iDiag=0; iDiag != 2; iDiag++) { */
/*       int iRow, iCol; */
/*       int nMineInThisDiag = 0; */
/*       int nHisInThisDiag = 0; */
/*       for (int iCounter=0; iCounter != 4; iCounter++) { */
/* 	switch (iDiag)  */
/* 	  { */
/* 	  case 0 : iRow=iCounter; iCol=iCounter; break; */
/* 	  case 1 : iRow=iCounter; iCol=4-iCounter; break; */
/* 	  default : break; */
/* 	  } */
/* 	Square mySquare = thisBoard.getSquare(iRow,iCol); */
/* 	if (mySquare.top()*PlayerToMove > 0)  */
/* 	  nMineInThisDiag++; */
/* 	if (mySquare.top()*PlayerToMove < 0) */
/* 	  nHisInThisDiag++; */
/*       } */
/*       if (nMineInThisDiag == 3) { */
/* 	NThreeInARows++; */
/*       } */
/*       if (nHisInThisDiag == 3) { */
/* 	NThreeInARows--; */
/*       } */
/*     } */

/*     (ListOfMovesWithThreeInARows[NThreeInARows+10]).push_back(*thisMove); */
/*   } */
/*   // Push-back contents of TriplesList onto OrderedList */
/*   //  in a reverse way.  (Most Triples for me come first) */
/*   for (int vectNum=20; vectNum>=0; vectNum--) { */
/*     for (vector<Move>::iterator thisMove = (ListOfMovesWithThreeInARows[vectNum]).begin(); */
/* 	 thisMove != (ListOfMovesWithThreeInARows[vectNum]).end(); */
/* 	 thisMove++) { */
/*       OrderedList.push_back(*thisMove); */
/*     } */
/*   } */
  

  //  EARLY TEST



/*   // Check things in the start squares first */
/*   for (vector<Move>::iterator thisMove = ListOfMoves.begin(); */
/*        thisMove != ListOfMoves.end(); ) { */
/*     if (!(thisMove->isOriginInPlayBoard())) { */
/*       OrderedList.push_back(*thisMove); */
/*       ListOfMoves.erase(thisMove); */
/*       continue; */
/*     } */
/*     thisMove++; */
/*   } */

/*   // Then go in decreasing order of gobblet size. */
/*   for (int gobbletSize=4; gobbletSize>=0; gobbletSize--) { */
/*     for (vector<Move>::iterator thisMove = ListOfMoves.begin(); */
/* 	 thisMove != ListOfMoves.end(); ) { */
/*       int row = thisMove->getOriginRow(); */
/*       int col = thisMove->getOriginCol(); */
/*       Square thisSquare = thisBoard.getSquare(row,col); */
/*       if (abs(thisSquare.top()) == gobbletSize) { */
/* 	OrderedList.push_back(*thisMove); */
/* 	ListOfMoves.erase(thisMove); */
/* 	continue; */
/*       } */
/*       thisMove++; */
/*     } */
/*   } */

/*   return OrderedList; */
}

vector<Move> Bot::ReorderMoves(vector<Move> ListOfMoves, Board thisBoard) {
  int PlayerToMove = thisBoard.getWhoseTurn();

/*   // Start of game, skip all this reordering */
/*   int NMyPiecesOnBoard = 0; */
/*   for (int iRow=0; iRow != 4; iRow++) { */
/*     for (int iCol=0; iCol != 4; iCol++) { */
/*       Square thisSquare = thisBoard.getSquare(iRow,iCol); */
/*       if (thisSquare.top()*PlayerToMove > 0) */
/* 	NMyPiecesOnBoard++; */
/*     } */
/*   } */
/*   if (NMyPiecesOnBoard < 3)  */
/*     return ListOfMoves; */


/*   vector<Move> OrderedList; */

  vector<Move> BigList;
  vector<Move> DiagBigList;
  vector<Move> NoSelfDiagBigList;

  // First (and least important) tweak, the bigger pieces the better
  for (int pieceSize=4; pieceSize > 0; pieceSize--) {
    for (vector<Move>::iterator thisMove = ListOfMoves.begin();
	 thisMove != ListOfMoves.end(); ) {
      int OriginRow = thisMove->getOriginRow();
      int OriginCol = thisMove->getOriginCol();
      Square thisSquare = thisBoard.getSquare(OriginRow,OriginCol);
      if (abs(thisSquare.top()) == pieceSize) {
	BigList.push_back(*thisMove);
	ListOfMoves.erase(thisMove);
	continue;
      }
      thisMove++;
    }
  }

  // Check moves to squares on diagonals before others
  for (vector<Move>::iterator thisMove = BigList.begin();
       thisMove != BigList.end(); ) {
    int DestinationRow = thisMove->getDestinationRow();
    int DestinationCol = thisMove->getDestinationCol();
    if ( (DestinationRow==DestinationCol) ||
	 (DestinationRow+DestinationCol==3) ) {
      DiagBigList.push_back(*thisMove);
      BigList.erase(thisMove);
      continue;
    }
    thisMove++;
  }
  for (vector<Move>::iterator thisMove = BigList.begin();
       thisMove != BigList.end(); ) {
    DiagBigList.push_back(*thisMove);
    BigList.erase(thisMove);
  }

  // Highest priority.  Examine moves that gobble your own LAST
  for (vector<Move>::iterator thisMove = DiagBigList.begin();
       thisMove != DiagBigList.end(); ) {
    int DestinationRow = thisMove->getDestinationRow();
    int DestinationCol = thisMove->getDestinationCol();
    Square thisSquare = thisBoard.getSquare(DestinationRow,DestinationCol);
    if (thisSquare.top()*PlayerToMove <= 0) {
      NoSelfDiagBigList.push_back(*thisMove);
      DiagBigList.erase(thisMove);
      continue;
    }
    thisMove++;
  }
  for (vector<Move>::iterator thisMove = DiagBigList.begin();
       thisMove != DiagBigList.end(); ) {
    NoSelfDiagBigList.push_back(*thisMove);
    DiagBigList.erase(thisMove);
  }

  return NoSelfDiagBigList;
}

float Bot::alphaBeta(Board thisBoard, int depth, float alpha, float beta) {
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
  /* ofstream empty; */
  /* vector<Move> OrderedMoves = ReorderMoves(LegalMoves,thisBoard, empty); */
  vector<Move> OrderedMoves = ReorderMoves(LegalMoves,thisBoard);
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
