#include <fstream>
#include <iostream>
#include <string>
#include <queue.h>
#include <stack.h>
#include "convertToPostfixNotation.h"
#include "print.h"
#include "solvePostfixNotation.h"

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inpFile;
  if (argc == 2)
  {
    inpFile.open(argv[1]);
    if (!inpFile.is_open())
    {
      std::cerr << "File isn't open\n";
      return 1;
    }
  }
  std::istream& input = argc == 1 ? std::cin : inpFile;
  try
  {
    mashkin::Queue< std::string > que;
    mashkin::Stack< int long long > result;
    while (input)
    {
      std::string line;
      std::getline(input, line);
      if (line.find_first_not_of(" \n") == std::string::npos)
      {
        continue;
      }
      line += " ";
      mashkin::convertToPostNot(line, que);
      result.push(solvePostfixNotation(que));
    }
    mashkin::print(result);
    std::cout << "\n";
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
