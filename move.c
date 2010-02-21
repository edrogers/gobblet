#include "move.h"
#include <iostream>
#include <string>
using namespace std;

bool Move::setOrigin(int row, int col)
{
  if ( (0 <= row) && (row < 4) &&
       (0 <= col) && (col < 4) ) {
    OriginRow = row;
    OriginCol = col;
    return true;
  } else if ( (4 <= row) && (row < 6) &&
	      (0 <= col) && (col < 3) ) {
    OriginRow = row;
    OriginCol = col;
    return true;
  } else {
    return false;
  }
}

bool Move::setDestination(int row, int col)
{
  if ( (0 <= row) && (row < 4) &&
       (0 <= col) && (col < 4) ) {
    DestinationRow = row;
    DestinationCol = col;
    return true;
  } else {
    return false;
  }
}

int Move::getOriginRow()
{
  return OriginRow;
}

int Move::getOriginCol()
{
  return OriginCol;
}

int Move::getDestinationRow()
{
  return DestinationRow;
}

int Move::getDestinationCol()
{
  return DestinationCol;
}

void Move::print()
{
  char orr;
  switch(OriginRow) 
    {
    case 0: orr = 'A'; break;
    case 1: orr = 'B'; break;
    case 2: orr = 'C'; break;
    case 3: orr = 'D'; break;
    case 4: orr = 'W'; break;
    case 5: orr = 'K'; break;
    default: break;
    }
  char dr;
  switch(DestinationRow) 
    {
    case 0: dr = 'A'; break;
    case 1: dr = 'B'; break;
    case 2: dr = 'C'; break;
    case 3: dr = 'D'; break;
    default: break;
    }

  cout << orr << OriginCol+1 << "->" << dr << DestinationCol+1;

}

bool Move::operator==(const Move &rhs)
{
  if( (this->OriginRow == rhs.OriginRow) &&
      (this->OriginCol == rhs.OriginCol) &&
      (this->DestinationRow == rhs.DestinationRow) &&
      (this->DestinationCol == rhs.DestinationCol) ) {
    return true;
  } else {
    return false;
  }
}

bool Move::operator!=(const Move &rhs)
{
  return (!( (*this)==rhs));
}

bool Move::isOriginInPlayBoard()
{
  if( (0 <= OriginRow) && (OriginRow < 4) &&
      (0 <= OriginCol) && (OriginCol < 4) )
    return true;
  else
    return false;
}

bool Move::isDestinationInPlayBoard()
{
  if( (0 <= DestinationRow) && (DestinationRow < 4) &&
      (0 <= DestinationCol) && (DestinationCol < 4) )
    return true;
  else
    return false;
}

bool Move::isOriginWhiteStart()
{
  if ( (OriginRow == 4) &&
       (0 <= OriginCol) && (OriginCol < 3) ) {
    return true;
  } else {
    return false;
  }
}

bool Move::isOriginBlackStart()
{
  if ( (OriginRow == 5) &&
       (0 <= OriginCol) && (OriginCol < 3) ) {
    return true;
  } else {
    return false;
  }
}

bool Move::isOriginLegal()
{
  if (isOriginInPlayBoard()) {
    return true;
  } else if ( (isOriginWhiteStart()) || 
	      (isOriginBlackStart()) ) {
    return true;
  } else {
    return false;
  }
}

bool Move::isDestinationLegal()
{
  if(isDestinationInPlayBoard()) {
    return true;
  } else {
    return false;
  }
}
