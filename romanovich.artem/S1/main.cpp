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
      //Queue< std::string > infixNotation = splitLine(line);
      Queue< Node<std::string> > infixNotation(Queue< Node<std::string> >);
      splitLine(infixNotation, line);
      Queue< std::string > postfixQueue = new Queue< std::string >;
      getPostfixFromInfix(postfixQueue, infixNotation);
      //postfixQueue->print();

      std::cout << calcPostfixExpression(postfixQueue);
/*      delete infixNotation;
      delete postfixQueue;*/
    }
  }
  return 0;
}
