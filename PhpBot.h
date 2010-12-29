#include <iostream>
#include <fstream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class PhpBot
{
 private:
  int playerNum;

  float Evaluate(Board thisBoard);
  std::vector<Move> ReorderMoves(std::vector<Move> ListOfMoves,Board thisBoard);
  float alphaBeta(Board thisBoard, int depth, float alpha, float beta);
 public:
  //constructors
  PhpBot();
  PhpBot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
