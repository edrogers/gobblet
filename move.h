// a move in Gobblet object
// 22 Dec 2005
#ifndef MOVE_H
#define MOVE_H

#include "move.h"
#include <string>
class Move
{
 private:
  int OriginRow; 
  int OriginCol;
  int DestinationRow; 
  int DestinationCol;
 public:
  Move();
  Move(std::string moveOrig, std::string moveDest);
  bool setOrigin(int row, int col);
  bool setDestination(int row, int col);
  int getOriginRow();
  int getOriginCol();
  int getDestinationRow();
  int getDestinationCol();

  void print();

  bool operator==(const Move &rhs);
  bool operator!=(const Move &rhs);

  bool isOriginInPlayBoard();
  bool isDestinationInPlayBoard();
  bool isOriginWhiteStart();
  bool isOriginBlackStart();
  bool isOriginLegal();
  bool isDestinationLegal();
};

#endif
