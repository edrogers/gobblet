// A square from the Gobblet board
// 22 Dec 2005
#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <string>

class Square
{
 private:
  std::vector<int> myStack;
 public:
  Square();
  Square(int player);
  Square(std::string SquareWord);
  std::string print(int row);
  void php_print(int squareNum,int movePart);
  void php_print_selected(int squareNum,int movePart);
  int getStackPhpCode();
  std::string locationNumToString(int squareLocation);
  std::vector<int> getmyStack();
  bool lift(int player);
  bool drop(int shell);
  int top(); //return just the top shell
  int second_from_top(); //return what's below the top shell
};

#endif
