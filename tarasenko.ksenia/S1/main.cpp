#include <iostream>
#include <string>
#include "fstream"
#include "queue.h"
#include "elem.h"
#include "transformStringToInfixQueue.h"
#include "transformInfixQueueToPostfix.h"
#include "calculateByPostfixQueue.h"

int main(int argc, char *argv[])
{
  std::ifstream input;
  if (argc == 2)
  {
    input.open(argv[1]);
    std::cin.rdbuf(input.rdbuf());
  }
  std::string str = "";
  Stack< int > results;
  while (std::getline(std::cin,str))
  {
    if (str.find_first_not_of(" \n\t") == std::string::npos) continue;
    try
    {
      Queue< Elem > q_infix = transformStringToInfixQueue< Elem >(str);
      Queue< Elem > q_postfix = transformInfixQueueToPostfix(q_infix);
      results.push(calculateByPostfixQueue< Elem >(q_postfix));
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
  while (!results.isEmpty())
  {
    std::cout << results.drop() << " ";
  }
  std::cout << "\n";
}
