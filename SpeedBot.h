#include <iostream>
#include <fstream>
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

class SpeedBot
{
 private:
  int playerNum;

  float Evaluate(Board thisBoard);
  int   nOtherPiecesThisRowAfterPlayerMoves(Board thisBoard, Move thisMove);
  int   nOtherPiecesThisColAfterPlayerMoves(Board thisBoard, Move thisMove);
  int   nOtherPiecesThisDiagAfterPlayerMoves(Board thisBoard, Move thisMove);
  bool  isAMoveToDiag(Move thisMove);
  int   nOpponentBigPiecesThisRowAfterPlayerMoves(Board thisBoard, Move thisMove);
  int   nOpponentBigPiecesThisColAfterPlayerMoves(Board thisBoard, Move thisMove);
  int   nOpponentBigPiecesThisDiagAfterPlayerMoves(Board thisBoard, Move thisMove);

  std::vector<Move> ReorderMoves(std::vector<Move> ListOfMoves,Board thisBoard);
  float alphaBeta(Board thisBoard, int depth, float alpha, float beta);
 public:
  //constructors
  SpeedBot();
  SpeedBot(int thisNum);

  int getPlayerNum();
  void setPlayerNum(int thisNum);

  Move chooseMove(Board thisBoard);
};
