#include <iostream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class alphaBot
{
 private:
  int playerNum;

 public:
  //constructors
  alphaBot();
  alphaBot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
