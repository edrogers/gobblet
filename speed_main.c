#include <iostream>
#include <vector>
#include <cstdlib>
#include "human.h"
#include "SpeedBot.h"
#include "Bot.h"
#include "move.h"
#include "square.h"
#include "board.h"
using namespace std;

int main()
{

  const int nROWS=4;
  const int nCOLS=4;
  const int nSTART=3;
  Square WhiteStartSquares[nSTART];
  Square BlackStartSquares[nSTART];
  Square PlayBoardSquares[nROWS][nCOLS];

  // Build board

  // White Start Squares
  for (int iSquare = 0; iSquare != nSTART; iSquare++) {
    string SquareWord;
    switch (iSquare) {
    case 0 : SquareWord.append("WWEE"); break;
    case 1 : SquareWord.append("WWEE"); break;
    case 2 : SquareWord.append("WWWE"); break;
    default : break; 
    }
    WhiteStartSquares[iSquare] = Square(SquareWord);
  }

  // Black Start Squares
  for (int iSquare = 0; iSquare != nSTART; iSquare++) {
    string SquareWord;
    switch (iSquare) {
    case 0 : SquareWord.append("BEEE"); break;
    case 1 : SquareWord.append("BBEE"); break;
    case 2 : SquareWord.append("BBEE"); break;
    default : break; 
    }
    BlackStartSquares[iSquare] = Square(SquareWord);
  }

  // Play Board Squares
  for (int iRow = 0; iRow != nROWS; iRow++) {
    for (int iCol = 0; iCol != nCOLS; iCol++) {
      string SquareWord;
      int SquareNum = iCol+4*iRow;
      switch(SquareNum) {
      case  0 : SquareWord.append("EEEB"); break;
      case  1 : SquareWord.append("EEWE"); break;
      case  2 : SquareWord.append("EEEE"); break;
      case  3 : SquareWord.append("EEBW"); break;
      case  4 : SquareWord.append("EEEE"); break;
      case  5 : SquareWord.append("EEBW"); break;
      case  6 : SquareWord.append("EEEW"); break;
      case  7 : SquareWord.append("EEEE"); break;
      case  8 : SquareWord.append("EEEE"); break;
      case  9 : SquareWord.append("EEEE"); break;
      case 10 : SquareWord.append("EEEB"); break;
      case 11 : SquareWord.append("EEBE"); break;
      case 12 : SquareWord.append("EBEE"); break;
      case 13 : SquareWord.append("EEEE"); break;
      case 14 : SquareWord.append("EEWE"); break;
      case 15 : SquareWord.append("EEEB"); break;
      default : break;
      }
      PlayBoardSquares[iRow][iCol] = Square(SquareWord);
    }
  }

  SpeedBot playerB(-1);
  /* Bot playerB(-1); */
  Board myBoard(WhiteStartSquares,BlackStartSquares,PlayBoardSquares,playerB.getPlayerNum());
  Move nextMove;

  nextMove = playerB.chooseMove(myBoard);
  myBoard.makeMove(nextMove,playerB.getPlayerNum());
  myBoard.print();

  return -1;
}


