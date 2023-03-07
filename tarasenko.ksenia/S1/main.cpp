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
    if (!(input.is_open()))
    {
      std::cout << "File not found\n";
      return 1;
    }
    std::cin.rdbuf(input.rdbuf());
  }
  std::string str = "";
  tarasenko::Stack< long long > results;
  while (std::getline(std::cin, str))
  {
    if (str.find_first_not_of(" \n\t") == std::string::npos)
    {
      continue;
    }
    try
    {
      tarasenko::Queue< tarasenko::Elem > q_infix = tarasenko::transformStringToInfixQueue(str);
      tarasenko::Queue< tarasenko::Elem > q_postfix = tarasenko::transformInfixQueueToPostfix(q_infix);
      results.push(tarasenko::calculateByPostfixQueue(q_postfix));
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
  if (!results.isEmpty())
  {
    std::cout << results.drop();
  }
  while (!results.isEmpty())
  {
    std::cout << " " << results.drop();
  }
  std::cout << "\n";
}
