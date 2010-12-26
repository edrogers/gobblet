#include <iostream>
#include <fstream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class Bot
{
 private:
  int playerNum;

  float Evaluate(Board thisBoard);
  std::vector<Move> ReorderMoves(std::vector<Move> ListOfMoves,Board thisBoard, ofstream& logfile);
  float alphaBeta(Board thisBoard, int depth, float alpha, float beta);
 public:
  //constructors
  Bot();
  Bot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
