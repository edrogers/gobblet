#include <iostream.h>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class Human
{
 private:
  int playerNum;

 public:
  //constructors
  Human();
  Human(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
