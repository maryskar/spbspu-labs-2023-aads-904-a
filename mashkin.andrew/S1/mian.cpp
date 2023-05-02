#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "convertToPostfixNotation.h"
#include "print.h"
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
    mashkin::Stack< std::string > result;
    while (std::cin)
    {
      std::string str;
      std::getline(input, str);
      if (str.find_first_not_of(" \n") == std::string::npos)
      {
        continue;
      }
    }
    print(result);
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
