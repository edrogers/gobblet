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
  Square(std::string php_code);
  std::string print(int row);
  void php_print();
  int getStackPhpCode();
  std::vector<int> getmyStack();
  bool lift(int player);
  bool drop(int shell);
  int top(); //return just the top shell
};

#endif
