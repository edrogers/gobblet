// a Gobblet board
// 22 Dec 2005
#include <cstdlib>
#include "board.h"
#include "move.h"
#include "square.h"
#include <iostream>
#include <vector>

#define ROWS 4
#define COLS 4

using namespace std;

Board::Board()
{
  Square EmptySquare;
  Square WhiteSquare(1);
  Square BlackSquare(-1);

  for(int i=0; i != ROWS; ++i) {
    for(int j=0; j != COLS; ++j) {
      playBoard[i][j] = EmptySquare;
    }
  }
  for(int i=0; i != 3; ++i) {
    whiteStart[i] = WhiteSquare;
    blackStart[i] = BlackSquare;
  }
  buildAllMoves();

  whoseTurn = 1;

}

Board::Board(string boardSquareState[4][4], string whiteStartSquareState[3], string blackStartSquareState[3])
{
  for(int i=0; i != ROWS; ++i) {
    for(int j=0; j != COLS; ++j) {
      playBoard[i][j] = Square(boardSquareState[i][j]);
    }
  }
  for(int i=0; i != 3; ++i) {
    whiteStart[i] = Square(whiteStartSquareState[i]);
    blackStart[i] = Square(blackStartSquareState[i]);
  }
  buildAllMoves();

  whoseTurn = 1;
}

void Board::buildAllMoves()
{
  allMoves.clear();
  Move thisMove;
  for(int i=0; i!=ROWS; ++i) {
    for(int j=0; j!=COLS; ++j) {
      for(int k=0; k!=ROWS; ++k) {
	for(int l=0; l!=COLS; ++l) {
	  if((i!=k) || (j!=l)) {
	    thisMove.setDestination(i,j);
	    thisMove.setOrigin(k,l);
	    allMoves.push_back(thisMove);
	  }	  
	}
      }
      for(int k=4; k!=6; ++k) {
	for(int l=0; l!=3; ++l) {
	  thisMove.setDestination(i,j);
	  thisMove.setOrigin(k,l);
	  allMoves.push_back(thisMove);
	}
      }
    }
  }
  return;
}

bool Board::hasFourInARow(int player) {
  if (player == 0) return false;

  int col[4];
  int row[4];
  int diag[4];

  for (int i=0; i!=COLS; ++i) {
    for (int j=0; j!=ROWS; ++j) {
      col[j] = (playBoard[j][i]).top();
    }
    bool foundyet = true;
    for (int j=0; j!=ROWS; ++j) {
      if (col[j]*player <= 0) 
	foundyet = false;
    }
    if(foundyet) return true;
  }

  for (int i=0; i!=ROWS; ++i) {
    for (int j=0; j!=COLS; ++j) {
      row[j] = (playBoard[i][j]).top();
    }
    bool foundyet = true;
    for (int j=0; j!=COLS; ++j) {
      if (row[j]*player <= 0) 
	foundyet = false;
    }
    if(foundyet) return true;
  }

  for (int i=0; i!=4; ++i) {
    diag[i] = (playBoard[i][i]).top();
  }
  bool foundyet = true;
  for (int i=0; i!=4; ++i) {
    if(diag[i]*player <= 0)
      foundyet = false;
  }
  if(foundyet) return true;

  for (int i=0; i!=4; ++i) {
    diag[i] = (playBoard[i][3-i]).top();
  }
  foundyet = true;
  for (int i=0; i!=4; ++i) {
    if(diag[i]*player <= 0)
      foundyet = false;
  }
  if(foundyet) return true;

  return false;

}

bool Board::tryMove(Move thisMove, int player) {
  int orr = thisMove.getOriginRow();
  int oc = thisMove.getOriginCol();
  int dr = thisMove.getDestinationRow();
  int dc = thisMove.getDestinationCol();

  Square origin = getSquare(orr, oc);
  Square destination = getSquare(dr, dc);

  int shellToMove = origin.top();

  // Can you drop this shell?   If not, stop right away
  if ( !((playBoard[dr][dc]).drop(shellToMove)) ) {
    return false;
  }

  if(thisMove.isOriginInPlayBoard()) {
    if ( !((playBoard[orr][oc]).lift(player)) ) {
      return false;
    }
  } else if (thisMove.isOriginWhiteStart()) {
    if ( !((whiteStart[oc]).lift(player)) ) {
      return false;
    }
  } else {
    if ( !((blackStart[oc]).lift(player)) ) {
      return false;
    }
  }
  
  return true;

}

bool Board::undoMove(Move thisMove, int player) {
  int orr = thisMove.getOriginRow();
  int oc = thisMove.getOriginCol();
  int dr = thisMove.getDestinationRow();
  int dc = thisMove.getDestinationCol();

  Square origin = getSquare(orr, oc);
  Square destination = getSquare(dr, dc);

  int shellToMove = destination.top();


  if ( !((playBoard[dr][dc]).lift(player)) ) {
    return false;
  }

  if(thisMove.isOriginInPlayBoard()) {
    if ( !((playBoard[orr][oc]).drop(shellToMove)) ) {
      return false;
    }
  } else if (thisMove.isOriginWhiteStart()) {
    if ( !((whiteStart[oc]).drop(shellToMove)) ) {
      return false;
    }
  } else {
    if ( !((blackStart[oc]).drop(shellToMove)) ) {
      return false;
    }
  }

  return true;
}

Square Board::getSquare(int row, int col) {
  if((row >= 0) && (row < ROWS+2) && 
     (col >= 0) && (col < COLS)) {
    if (row >= ROWS) {
      if(col < 3) {
	if(row == 4) {
	  return getStartSquare(1,col);
	} else {
	  return getStartSquare(-1,col);
	}
      } else {
	Square invalid;
	return invalid;
      }
    } else {
      return playBoard[row][col];
    }
  } else {
    Square invalid;
    return invalid;
  }
}

Square Board::getPlaySquare(int row, int col) {
  if((row >= 0) && (row < ROWS) && 
     (col >= 0) && (col < COLS)) {
    return playBoard[row][col];
  } else {
    Square invalid;
    return invalid;
  }
}

Square Board::getStartSquare(int player, int num) {
  if(num < 3) {
    if (player > 0) {
      return whiteStart[num];
    } else if (player < 0) {
      return blackStart[num];
    }
  } else {
    Square invalid;
    return invalid;
  }
}

int Board::getWhoseTurn() {
  return whoseTurn;
}

void Board::print()
{
  bool displayMoves = true;

  cout << endl;
  cout << "      ";
  for(int j=0; j!=3; ++j) {
    cout << "   " << j+1 << "   " << "   ";
  }
  cout << endl;

  for (int i=0; i!=7; ++i) {
    if ( i != 3 )
      cout << "      ";
    else
      cout << "   W  ";
    for (int j=0; j!=3; ++j) {
      cout << (whiteStart[j]).print(i);
      cout << "   ";
    }
    cout << endl;
  }
  cout << endl;

  cout << " ";
  for (int i=0; i!=ROWS; ++i) {
    cout << "   " << i+1 << "   " << "   ";
  }

  vector<Move> myMoves;
  myMoves = getAllLegalMoves(whoseTurn);
  int numMoves = myMoves.size();
  int lineCount = 0;
  //  if (numMoves < 9) displayMoves = true;
  if (hasWon(-1*whoseTurn)) {
    displayMoves = false;
  }
  if (displayMoves) {
    cout << "All " << numMoves << " Legal Moves:";
  }

  for (int h=0; h!=ROWS; ++h) {
    cout << endl;
    for(int i=0; i!=7; ++i) {
      char row;
      switch(h) 
	{
	case 0: row = 'A'; break;
	case 1: row = 'B'; break;
	case 2: row = 'C'; break;
	case 3: row = 'D'; break;
	default: break;
	}
	  
      if (i != 3) 
	cout << " ";
      else
	cout << row;
      
      for(int j=0; j!=COLS; ++j) {
	cout << (playBoard[h][j]).print(i);
	cout << "   ";
      }
      if (displayMoves) {
	if(lineCount < 28) {
	  if(numMoves > 0) {
	    if(lineCount < numMoves) {
	      streamsize oldwidth = cout.width();
	      cout.width(2);
	      cout << lineCount+1 << ". ";
	      cout.width(oldwidth);
	      (myMoves[lineCount]).print();
	      cout << "   ";
	    }
	    if(numMoves > 28) {
	      if(lineCount+28 < numMoves) {
		cout << lineCount+29 << ". ";
		(myMoves[lineCount+28]).print();
		cout << "   ";
	      }
	      if(numMoves > 56) {
		if(lineCount+56 < numMoves) {
		  cout << lineCount+57 << ". ";
		  (myMoves[lineCount+56]).print();
		  cout << "   ";
		}
		if(numMoves > 84) {
		  if(lineCount+84 < numMoves) {
		    streamsize oldwidth = cout.width();
		    cout.width(3);
		    cout << lineCount+85 << ". ";
		    cout.width(oldwidth);
		    (myMoves[lineCount+84]).print();
		    cout << "   ";
		  }
		  if(numMoves > 112) {
		    if(lineCount+112 < numMoves) {
		      cout << lineCount+113 << ". ";
		      (myMoves[lineCount+112]).print();
		      cout << "   ";
		    }
		    if(numMoves > 140) {
		      if(lineCount+140 < numMoves) {
			cout << lineCount+141 << ". ";
			(myMoves[lineCount+140]).print();
			cout << "   ";
		      }
		      if(numMoves > 168) {
			if(lineCount+168 < numMoves) {			
			  cout << lineCount+169 << ". ";
			  (myMoves[lineCount+168]).print();
			  cout << "   ";
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	  lineCount++;
	}
      }
      cout << endl;
    }
  }

  cout << endl;
  cout << "      ";
  for(int j=0; j!=3; ++j) {
    cout << "   " << j+1 << "   " << "   ";
  }
  cout << endl;

  for (int i=0; i!=7; ++i) {
    if ( i != 3 )
      cout << "      ";
    else
      cout << "   K  ";
    for (int j=0; j!=3; ++j) {
      cout << (blackStart[j]).print(i);
      cout << "   ";
    }
    cout << endl;
  }
  /*** everything after here is test-code ***/
  
  /*** everything before here is test-code ***/
}

void Board::php_print()
{
  for (int j=0; j!=3; ++j) {
    whiteStart[j].php_print();
  }
  for (int h=0; h!=ROWS; ++h) {
    for(int j=0; j!=COLS; ++j) {
      playBoard[h][j].php_print();
    }
  }
  for (int j=0; j!=3; ++j) {
    blackStart[j].php_print();
  }
  cout << endl;
  return;
}

bool Board::isLegal(Move thisMove, int player) {
  vector<Move>::iterator iter;

  //  cout << "Checking Legality of " << thisMove.print() << endl;


  /** First, check to see if the move could *ever* be legal     **/
  /** Excludes attempts to move back to origin and off of board **/
  bool foundyet = false;
  for(iter = allMoves.begin(); ( (iter != allMoves.end()) && (!(foundyet)) ); iter++) {
    if((*iter) == thisMove)
      foundyet = true;
  }

  if(!(foundyet)) return false;

  int orr = thisMove.getOriginRow();
  int oc = thisMove.getOriginCol();
  int dr = thisMove.getDestinationRow();
  int dc = thisMove.getDestinationCol();

  Square origin = getSquare(orr, oc);
  Square destination = getSquare(dr, dc);

  /** Now check to see that the origin has one of player's shells on top **/
  if(origin.top()*player <= 0) {
    return false;
    /** and check to see that it can gobble whatever is at destination **/
  } else if (abs(origin.top()) <= abs(destination.top())) {
    return false;
  }

  if (tryMove(thisMove, player)) {

    /** Next, check to see that the move doesn't give away the game **/
    if ( hasFourInARow((-1)*(player)) ) {
      undoMove(thisMove, player);
      return false;
    }

    undoMove(thisMove, player);
  }
  /* If it passes all those tests, it must be legal */
  return true;
 
}

vector<Move> Board::getAllLegalMoves(int player) {
  vector<Move> moves = allMoves;
  vector<Move>::iterator iter;
  
  for(iter = moves.end()-1; iter >= moves.begin(); iter--) {
    if(!(isLegal(*iter, player))) {
      moves.erase(iter);
    }
  }
  
  return moves;
}

bool Board::makeMove(Move thisMove, int player) {
  if( (player*whoseTurn > 0 ) && (isLegal(thisMove, player)) ) {
    whoseTurn *= -1;
    if(tryMove(thisMove, player)) {
      return true;
    } else {
      whoseTurn *= -1;
      return false;
    }
  } else {
    return false;
  }
}

Board Board::testMove(Move thisMove, int player) {
  /** Returns a copy of the current board, modified by thisMove **/
  if( (isLegal(thisMove, player)) && (player*whoseTurn > 0) ) {
    if (tryMove(thisMove, player)) {
      whoseTurn *= -1;
      Board output(*this);
      whoseTurn *= -1;
      undoMove(thisMove, player);
      return output;
    } else {
      Board invalid;
      return invalid;
    }
  } else {
    Board invalid;
    return invalid;
  }
}

bool Board::hasWon(int player) {
  int otherplayer = (-1)*player;

  if(hasFourInARow(otherplayer))
    return false;

  if(hasFourInARow(player))
    return true;

  vector<Move> moves;
  moves = getAllLegalMoves(otherplayer);

  if (moves.size() > 0) {
    return false;
  } else {
    return true;
  }

}
