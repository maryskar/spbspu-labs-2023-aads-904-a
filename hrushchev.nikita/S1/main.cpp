#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error arg\n";
    return 1;
  }
  
  std::ifstream file_input;
  if(argc == 2)
  {
    std::ifstream file_input(argv[1]);
    if (!file_input)
    {
      std::cerr << "Unable to open file: " << argv[1] << "\n";
      return 1;
    }
  }  
  std::istream& input = (argc == 2) ? file_input : std::cin;

  std::string line;
  Stack < long long > results;
  while (std::getline(input, line))
  {
    if (!input)
    {
      break;
    }
    if (line.empty())
    {
      continue;
    }
    Queue< std::string > infix = convertStringToInfix(line);
    try
    {
      Queue< std::string > postfix = convertInfixToPostfix(infix);
      long long result = calculatePostfix(postfix);
      results.push(result);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << "\n";
      return 2;
    }
  }
  if (!results.isEmpty())
  {
    std::cout << results.get();
    results.pop();
    while (!results.isEmpty())
    {
      std::cout << " " << results.get();
      results.pop();
    }
  }
  std::cout << "\n";
}

