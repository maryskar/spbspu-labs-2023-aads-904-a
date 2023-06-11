#include <iostream>
#include <string>
#include "queue.h"
#include "stringToInfix.h"
#include "convertToPostfix.h"
#include "solvePostfixExpr.h"
void printQueueElements(aksenov::Queue< std::string > &queue)
{
  while (!queue.isEmpty())
  {
    std::string element;
    if (!queue.isEmpty())
    {
      element = queue.drop();
      queue.pop();
    }
    std::cout << element << std::endl;
  }
}

int main()
{
  std::string str = "( 3 + 2 ) / 5 - 1";
  try {
    aksenov::Queue< std::string > queue = aksenov::convertToInfix(str);
    aksenov::Queue< std::string > postfixQ = aksenov::getPostfixQueue(queue);
    //printQueueElements(postfixQ);
    std::cout << aksenov::solvePostfixExpr(postfixQ);
  } catch (const std::invalid_argument& e) {
    std::cout << "Invalid argument: " << e.what() << std::endl;
  }
  return 0;
}
