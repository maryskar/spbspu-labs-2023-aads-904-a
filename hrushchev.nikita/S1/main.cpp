#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "queue.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error arg\n";
    return 1;
  }

  if(argc == 2)
    {
    std::ifstream input(argv[1]);
    if (!input)
    {
      std::cerr << "Unable to open file: " << argv[1] << "\n";
      return 1;
    }

    std::string line;
    while (getline(input, line))
    {
      if (!std::cin)
      {
        break;
      }
      if (line.empty())
      {
        continue;
      }      
      try
      {
        Queue< std::string > infix = convertStringToInfix(line);
        Queue< std::string > postfix = convertInfixToPostfix(infix);
        std::cout << calculatePostfix(postfix) << "\n";
      }
      catch (const std::exception& e)
      {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
      }
    }
  input.close();
  }
  else
  {
    std::string line;
    while (std::cin)
    {
      getline(std::cin, line)
      if (!std::cin)
      {
        break;
      }
      if (line.empty())
      {
        continue;
      }
      try
      {
        Queue< std::string > infix = convertStringToInfix(line);
        Queue< std::string > postfix = convertInfixToPostfix(infix);
        std::cout << calculatePostfix(postfix) << "\n";
      }
      catch (const std::exception& e)
      {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
      }
    } 
  }
}

