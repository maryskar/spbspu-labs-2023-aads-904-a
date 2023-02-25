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
  while (std::getline(std::cin,str))
  {
    try
    {
      Queue< Elem > q_infix = transformStringToInfixQueue< Elem >(str);
      Queue< Elem > q_postfix = transformInfixQueueToPostfix(q_infix);
      // buffer of answers
      int result = calculateByPostfixQueue< Elem >(q_postfix);
      std::cout << result << "\n";
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
}
