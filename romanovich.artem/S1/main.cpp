#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
#include "notations.h"
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  romanovich::Stack< std::string > stack;
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
  std::istream& in = (argc == 2) ? fileInput : std::cin;
  romanovich::Stack< std::string > answer;
  for (std::string line; std::getline(in, line);)
  {
    if (line.empty())
    {
      continue;
    }
    romanovich::Queue< std::string > infixNotation = romanovich::splitLine(line);
    romanovich::Queue< std::string > postfixQueue = romanovich::getPostfixFromInfix(infixNotation);
    try
    {
      romanovich::calcPostfixExpression(postfixQueue, &answer);
    }
    catch (...)
    {
      std::cerr << "Error while calc.\n";
      return 2;
    }
  }
  if (!answer.isEmpty())
  {
    std::cout << answer.pop();
    while (!answer.isEmpty())
    {
      std::cout << " " << answer.pop();
    }
    std::cout << "\n";
  }
  return 0;
}
