#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "print.h"
#include "convertToPostfixNotation.h"
#include "solvePostfixNotation.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    try
    {
      mashkin::Stack< std::string > stc;
      mashkin::Queue< std::string > que;
      mashkin::Stack< std::string > result;
      while (std::cin)
      {
        std::string str;
        std::getline(std::cin, str);
        if (str.empty())
        {
          break;
        }
        std::istringstream inpStr(str);
        que = convertToPostfixNotation(inpStr, stc, que);
        result.push(solvePostfixNotation(que));
      }
      print(result);
    }
    catch (const std::exception& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  }
  else if (argc == 2)
  {
    mashkin::Stack< std::string > stc;
    mashkin::Queue< std::string > que;
    std::ifstream inpFile;
    try
    {
      inpFile.open(argv[1]);
      if (!inpFile.is_open())
      {
        std::cerr << "File isn't open\n";
        return 1;
      }
      mashkin::Stack< std::string > result;
      while (inpFile)
      {
        std::string str;
        std::getline(inpFile, str);
        if (str.empty())
        {
          break;
        }
        std::istringstream inpStr(str);
        que = convertToPostfixNotation(inpStr, stc, que);
        result.push(solvePostfixNotation(que));
      }
      print(result);
    }
    catch (const std::exception& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  }
  std::cout << "\n";
  return 0;
}
