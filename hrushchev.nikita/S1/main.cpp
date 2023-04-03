#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "queue.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error arg\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Unable to open file: " << argv[1] << "\n";
    return 1;
  }

  std::string line;
  while (getline(input, line))
  {
    Queue< std::string > infix = convertStringToInfix(line);
    Queue< std::string > postfix = convertInfixToPostfix(infix);
    std::cout << calculatePostfix(postfix);
  }

  input.close();

  return 0;
}

