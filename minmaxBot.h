#include <iostream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class minmaxBot
{
 private:
  int playerNum;

  float Evaluate(Board thisBoard);

 public:
  //constructors
  minmaxBot();
  minmaxBot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
