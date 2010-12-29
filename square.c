#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "square.h"
using namespace std;

Square::Square()
{
  myStack.clear();
}

Square::Square(int player)
{
  if (player < 0) {
    player = -1;
  } else if (player > 0) {
    player = 1;
  }

  for(int i=1; i<5; ++i)
    {
      myStack.push_back(player*i);
    }

  if (player == 0) {
    myStack.clear();
  }

}

Square::Square(string php_code)
{
  int php_code_word = atoi(php_code.c_str());
  int php_word[4] = { 0 };
  for(int php_code_letter = 0; 
      php_code_letter != 4; 
      php_code_letter++) {
    php_word[php_code_letter] = (int) (php_code_word/(pow(3.0,php_code_letter*1.0)))%3;
  }

  for(int i=1; i<5; ++i)
    {
      if ((php_word[i-1]-1) != 0) {
	myStack.push_back((php_word[i-1]-1)*i);
      }
    }
}

std::string Square::print(int row)
{
  string output;
  string black = "\033[40;46m";
  string white = "\033[40;45m";
  string reset = "\033[m";
  vector<int>::iterator iter;
  vector<int>::iterator begin = myStack.begin();
  vector<int>::iterator end = myStack.end();

  if(myStack.size() == 0) {
    return "       ";
  }

  if ((row == 0) || (row == 6)) {
    if (abs(myStack.back()) == 4) { 
      if (myStack.back() > 0 ) { 
	output.append(white); 
      } else { 
	output.append(black); 
      } 
      output.append("*******"); 
      output.append(reset);
    } else {
      output.append("       ");
    }
  } else if ((row == 1) || (row == 5)) {

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 3 or -3, add the row of stars */
    iter = find(begin,end,3);
    if(iter == myStack.end()) iter = find(begin,end,-3);
    if(iter != myStack.end()) { //if you've found a 3 or -3
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*****");
      output.append(reset);
    } else {
      output.append("     ");
    }

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

  } else if ((row == 2) || (row == 4)) {

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 3 or -3, add the outside stars */
    iter = find(begin,end,3);
    if(iter == myStack.end()) iter = find(begin,end,-3);
    if(iter != myStack.end()) { //if you've found a 3 or -3
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 2 or -2, add the row of stars */ 
    iter = find(begin,end,2);
    if(iter == myStack.end()) iter = find(begin,end,-2);
    if(iter != myStack.end()) { //if you've found a 2 or -2
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("***");
      output.append(reset);
    } else {
      output.append("   ");
    }

    /* if there is a 3 or -3, add the outside stars */
    iter = find(begin,end,3);
    if(iter == myStack.end()) iter = find(begin,end,-3);
    if(iter != myStack.end()) { //if you've found a 3 or -3
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }
    
  } else if (row == 3) {

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 3 or -3, add the outside stars */
    iter = find(begin,end,3);
    if(iter == myStack.end()) iter = find(begin,end,-3);
    if(iter != myStack.end()) { //if you've found a 3 or -3
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 2 or -2, add the outside stars */
    iter = find(begin,end,2);
    if(iter == myStack.end()) iter = find(begin,end,-2);
    if(iter != myStack.end()) { //if you've found a 2 or -2
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 1 or -1, add the row of stars */ 
    iter = find(begin,end,1);
    if(iter == myStack.end()) iter = find(begin,end,-1);
    if(iter != myStack.end()) { //if you've found a 1 or -1
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 2 or -2, add the outside stars */
    iter = find(begin,end,2);
    if(iter == myStack.end()) iter = find(begin,end,-2);
    if(iter != myStack.end()) { //if you've found a 2 or -2
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 3 or -3, add the outside stars */
    iter = find(begin,end,3);
    if(iter == myStack.end()) iter = find(begin,end,-3);
    if(iter != myStack.end()) { //if you've found a 3 or -3
      if(*iter > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }

    /* if there is a 4 or -4, add the outside stars */
    if(abs(myStack.back()) == 4) {
      if(myStack.back() > 0) {
	output.append(white);
      } else {
	output.append(black);
      }
      output.append("*");
      output.append(reset);
    } else {
      output.append(" ");
    }
  }
  return output;
}

void Square::php_print() {
  cout << " " << getStackPhpCode();
}

int Square::getStackPhpCode()
{
  int code = 40;
  for (vector<int>::iterator it = myStack.begin();
       it != myStack.end();
       it++) {
    if((*it) > 0) {
      code+=pow(3.0,1.0*(abs((*it)-1)));
    } else {
      code-=pow(3.0,1.0*(abs(*it)-1));
    }
  }
  return code;
}

std::vector<int> Square::getmyStack()
{
  return myStack;
}

bool Square::lift(int player)
{
  if(myStack.size() > 0) {
    if(player*myStack.back() > 0) {
      myStack.pop_back();
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Square::drop(int shell)
{
  if(myStack.size() < 4) {
    if(myStack.size() == 0) {
      myStack.push_back(shell);
      return true;
    } else {
      if(abs(shell) > abs(myStack.back())) {
	myStack.push_back(shell);
	return true;
      } else {
	return false;
      }
    }
  } else {
    return false;
  }
}

int Square::top()
{
  if(myStack.size() > 0) 
    return myStack.back();
  else
    return 0;
}
