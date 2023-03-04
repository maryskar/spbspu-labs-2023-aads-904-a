#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
#include "node.h"
#include "notations.h"
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  Stack< std::string > stack = Stack< std::string >();
  if (argc == 2)
  {
    std::string fileIn = argv[1];
    std::fstream fileInput(fileIn);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file " << fileIn << ".\n";
      return 1;
    }
    for (std::string line; std::getline(fileInput, line);)
    {
      std::cout << line << "\n";
    }
  }
  else
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      Queue< std::string > infixNotation = splitLine(line);
      Queue< std::string > postfixQueue = getPostfixFromInfix(infixNotation);
      /////////////////////////////postfixQueue.print();
      /////////////////////////////std::cout << "!!!\n";

      ///
      Stack< std::string > *stack = new Stack< std::string >;
      stack->push(postfixQueue.pop());
      while (stack->getSize() >= 1)
      {
        std::string el;
        if (!postfixQueue.isEmpty())
        {
          el = postfixQueue.pop();
        }
        else
        {
          break;
        }
        //std::cout << "  " << el << std::endl;
        //stack->print();
        //std::cout << "\n";
        if (isDigit(el))
        {
          stack->push(el);
        }
        else
        {
          std::string x = stack->pop();
          std::string y = stack->pop();
          stack->push(doOperation(std::stol(x, nullptr, 10), std::stol(y, nullptr, 10), el));
        }
      }
      ///

      std::cout << std::stol(stack->top_->data_, nullptr, 10);
      //std::cout << calcPostfixExpression(infixNotation);
    }
  }
  return 0;
}
