#include <cstdlib>
#include <iostream>
#include "human.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

Human::Human()
{
  playerNum = 1;
}

Human::Human(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

int Human::getPlayerNum()
{
  return playerNum;
}

void Human::setPlayerNum(int thisNum)
{
  if(thisNum < 0)
    playerNum = -1;
  else
    playerNum = 1;
}

Move Human::chooseMove(Board thisBoard){  
  int whoseTurn = thisBoard.getWhoseTurn();

  if(whoseTurn*playerNum <= 0) {
    Move invalid;
    return invalid;
  }

  thisBoard.print();
  cout << endl;

  Move userMove;
  vector<Move> allLegal = thisBoard.getAllLegalMoves(whoseTurn);
  vector<Move>::iterator iter;

  char* white = "\033[40;45m";
  char* black = "\033[40;46m";
  char* reset = "\033[m";

  cout << "It is ";
  if (whoseTurn > 0)
    cout << white << "WHITE";
  else
    cout << black << "BLACK";

  cout << reset << "'s turn" << endl;

  /*** get OriginRow ***/

  bool legalORR[6] = {false, false, false, false, false, false};
  for(iter = allLegal.begin(); iter != allLegal.end(); iter++) {
    legalORR[iter->getOriginRow()] = true;
  }

  cout << "Move piece FROM what row? ";
  cout << "(";

  bool anyBefore = false;
  for(int i=0; i!=6; ++i) {
    if(legalORR[i]) {
      if(anyBefore)
	cout << ", ";
      char output;
      switch(i) 
	{
	case 0: output = 'A'; break;
	case 1: output = 'B'; break;
	case 2: output = 'C'; break;
	case 3: output = 'D'; break;
	case 4: output = 'W'; break;
	case 5: output = 'K'; break;
	default: break;
	}
      cout << output;
      anyBefore = true;
    }
  }
  cout << "): ";

  int orr = -1;

  char input;
  cin >> input;
  switch(input)
    {
    case 'A': if(legalORR[0]) orr = 0; break;
    case 'B': if(legalORR[1]) orr = 1; break;
    case 'C': if(legalORR[2]) orr = 2; break;
    case 'D': if(legalORR[3]) orr = 3; break;
    case 'W': if(legalORR[4]) orr = 4; break;
    case 'K': if(legalORR[5]) orr = 5; break;
    default: break;
    }
  /****************************/

  /*** get OriginCol ***/

  bool legalOC[4] = {false, false, false, false};
  for(iter = allLegal.begin(); iter != allLegal.end(); iter++) {
    if(iter->getOriginRow() == orr)
      legalOC[iter->getOriginCol()] = true;
  }

  cout << "Move piece FROM what column? ";
  cout << "(";

  anyBefore = false;
  for(int i=0; i!=4; ++i) {
    if(legalOC[i]) {
      if(anyBefore)
	cout << ", ";
      cout << i+1;
      anyBefore = true;
    }
  }
  if(!(anyBefore)) cout << "invalid";

  cout << "): ";

  int oc = -1;
  cin >> oc;
  oc -= 1;
  /****************************************/

  /*** get DestinationRow ***/

  bool legalDR[4] = {false, false, false, false};
  for(iter = allLegal.begin(); iter != allLegal.end(); iter++) {
    if((iter->getOriginRow() == orr) && (iter->getOriginCol() == oc))
      legalDR[iter->getDestinationRow()] = true;
  }

  cout << "Move piece TO what row? ";
  cout << "(";

  anyBefore = false;
  for(int i=0; i!=4; ++i) {
    if(legalDR[i]) {
      if(anyBefore)
	cout << ", ";
      char output;
      switch(i) 
	{
	case 0: output = 'A'; break;
	case 1: output = 'B'; break;
	case 2: output = 'C'; break;
	case 3: output = 'D'; break;
	default: break;
	}
      cout << output;
      anyBefore = true;
    }
  }
  cout << "): ";

  int dr = -1;

  cin >> input;
  switch(input)
    {
    case 'A': if(legalDR[0]) dr = 0; break;
    case 'B': if(legalDR[1]) dr = 1; break;
    case 'C': if(legalDR[2]) dr = 2; break;
    case 'D': if(legalDR[3]) dr = 3; break;
    default: break;
    }
  /****************************/

  /*** get DestinationCol ***/

  bool legalDC[4] = {false, false, false, false};
  for(iter = allLegal.begin(); iter != allLegal.end(); iter++) {
    if((iter->getOriginRow() == orr) && 
       (iter->getOriginCol() == oc) && 
       (iter->getDestinationRow() == dr))
      legalDC[iter->getDestinationCol()] = true;
  }

  cout << "Move piece TO what column? ";
  cout << "(";

  anyBefore = false;
  for(int i=0; i!=4; ++i) {
    if(legalDC[i]) {
      if(anyBefore)
	cout << ", ";
      cout << i+1;
      anyBefore = true;
    }
  }
  if(!(anyBefore)) cout << "invalid";

  cout << "): ";

  int dc = -1;
  cin >> dc;
  dc -= 1;
  /****************************************/

  bool success = false;
  success = ((userMove.setOrigin(orr,oc)) && (userMove.setDestination(dr,dc)));
  /*
  if(success) {
    cout << "Successfully input move: ";
    userMove.print();
  } else {
    cout << "Failed to input move";
  }
  */

  return userMove;
}
