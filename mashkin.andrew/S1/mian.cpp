#include <fstream>
#include <iostream>
#include <string>
#include "convertToPostfixNotation.h"
#include "queue.h"
#include "solvePostfixNotation.h"
#include "stack.h"

int main(int argc, char** argv)
{
  std::ifstream inpFile;
  inpFile.open(argv[1]);
  if (!inpFile.is_open())
  {
    std::cerr << "File isn't open\n";
    return 1;
  }
  std::istream& input = argc == 1 ? std::cin : inpFile;
  try
  {
    mashkin::Stack< std::string > stc;
    mashkin::Queue< std::string > que;
    std::string result;
    while (input)
    {
      std::string line;
      std::getline(input, line);
      if (line.find_first_not_of(" \n") == std::string::npos)
      {
        continue;
      }
      line += " ";
      mashkin::convertToPostNot(line, stc, que);
      result = solvePostfixNotation(que);
    }
    std::cout << result << "\n";
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
