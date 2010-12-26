#include <iostream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class betaBot
{
 private:
  int playerNum;

 public:
  //constructors
  betaBot();
  betaBot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
