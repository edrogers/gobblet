// a Gobblet board
// 22 Dec 2005
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "move.h"
#include "square.h"

#define ROWS 4
#define COLS 4

using namespace std;

class Board
{
 private:
  //member-data
  Square playBoard[ROWS][COLS]; // The board of play
  Square whiteStart[3];         // White's starting stacks
  Square blackStart[3];         // Black's starting stacks
  int whoseTurn;
  vector<Move> allMoves; // all origin-destination combos

  //member-functions
  bool hasFourInARow(int player);
  bool tryMove(Move thisMove, int player); // simply applies Move -- doesn't check anything -- private only
  bool undoMove(Move thisMove, int player); // same as above

 public:
  //default constructor
  Board();

  //member accessors
  Square getSquare(int row, int col);
  Square getPlaySquare(int row, int col);
  Square getStartSquare(int player, int num);
  int getWhoseTurn();

  //member functions
  void print();
  bool isLegal(Move thisMove, int player); //can player make Move
  vector<Move> getAllLegalMoves(int player);
  bool makeMove(Move thisMove, int player);
  Board testMove(Move thisMove, int player);
  bool hasWon(int player);     // has player currently won
};

#endif



