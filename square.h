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
  std::string print(int row);
  std::vector<int> getmyStack();
  bool lift(int player);
  bool drop(int shell);
  int top(); //return just the top shell
};

#endif
