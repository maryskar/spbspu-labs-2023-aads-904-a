#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
#include "notations.h"
#include "expressionpart.h"
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  romanovich::Stack< ExpPart > stack;
  std::fstream fileInput;
  if (argc == 2)
  {
    fileInput.open(argv[1]);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file.\n";
      return 1;
    }
    if (fileInput.eof())
    {
      std::cout << "\n";
      return 0;
    }
  }
  std::istream &in = (argc == 2) ? fileInput : std::cin;
  romanovich::Stack< ExpPart > answer;
  for (std::string line; std::getline(in, line);)
  {
    if (line.empty())
    {
      continue;
    }
    if (line == "^Z")
    {
      break;
    }
    romanovich::Queue< ExpPart > postfixQueue;
    romanovich::Stack< ExpPart > stack1;
    try
    {
      romanovich::Queue< ExpPart > infixNotation = romanovich::splitLine(line);
      romanovich::getPostfixFromInfix(infixNotation, stack1, postfixQueue);
    }
    catch (...)
    {
      std::cerr << "Error while calc.\n";
      return 2;
    }
    romanovich::Stack< ExpPart > calcStack;
    try
    {
      romanovich::calcPostfixExpression(postfixQueue, answer, calcStack);
    }
    catch (...)
    {
      std::cerr << "Error while calc.\n";
      return 2;
    }
  }
  if (!answer.isEmpty())
  {
    std::cout << answer.get().getOperand();
    answer.pop();
    while (!answer.isEmpty())
    {
      std::cout << " " << answer.get().getOperand();
      answer.pop();
    }
  }
  std::cout << "\n";
  return 0;
}
