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
  Stack< std::string > stack = Stack< std::string >();
  std::fstream fileInput;
  if (argc == 2)
  {
    fileInput.open(argv[1]);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file.\n";
      return 1;
    }
    if (fileInput.peek() == std::ifstream::traits_type::eof())
    {
      std::cout << "\n";
      return 0;
    }
    std::cin.rdbuf(fileInput.rdbuf());
  }
  std::istream& in = (argc == 2) ? fileInput : std::cin;
  Stack< std::string > answer;
  for (std::string line; std::getline(in, line);)
  {
    if (line.empty())
    {
      continue;
    }
    Queue< std::string > infixNotation = splitLine(line);
    Queue< std::string > postfixQueue = getPostfixFromInfix(infixNotation);
    try
    {
      calcPostfixExpression(postfixQueue, &answer);
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
