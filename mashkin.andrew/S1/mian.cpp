#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "convertToPostfixNotation.h"
#include "solvePostfixNotation.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char** argv)
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "Incorrect arguments\n";
    return 1;
  }
  else if (argc == 3)
  {
    mashkin::Stack< std::string > stc;
    mashkin::Queue< std::string > que;
    std::ifstream inpFile;
    try
    {
      inpFile.open(argv[2]);
      if (!inpFile.is_open())
      {
        std::cerr << "File isn't open\n";
        return 1;
      }
      que = convertToPostfixNotation(inpFile, stc, que);
      std::string result = solvePostfixNotation(que);
      std::cout << result << "\n";
    }
    catch (const std::underflow_error& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
    catch (const std::exception& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  }
  else
  {
  }
  return 0;
}
