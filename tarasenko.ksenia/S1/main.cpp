#include <iostream>
#include <string>
#include "fstream"
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "transformStringToInfixQueue.h"
#include "transformInfixQueueToPostfix.h"
#include "calculateByPostfixQueue.h"

int main(int argc, char *argv[])
{
  std::ifstream input;
  if (argc > 1)
  {
    input.open(argv[1]);
    if (!(input.is_open()))
    {
      std::cout << "File not found\n";
      return 1;
    }
  }
  std::istream& in = (argc == 2) ? input : std::cin;
  std::string str = "";
  tarasenko::Stack< long long > results;
  while (std::getline(in, str))
  {
    if (str.find_first_not_of(" \n\t") == std::string::npos)
    {
      continue;
    }
    try
    {
      tarasenko::Queue< tarasenko::Elem > q_infix = tarasenko::transformStringToInfixQueue(str);
      tarasenko::Queue< tarasenko::Elem > q_postfix = tarasenko::transformInfixQueueToPostfix(q_infix);
      long long res = tarasenko::calculateByPostfixQueue(q_postfix);
      results.push(res);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
  if (!results.isEmpty())
  {
    std::cout << results.getTopElem();
    results.pop();
  }
  while (!results.isEmpty())
  {
    std::cout << " " << results.getTopElem();
    results.pop();
  }
  std::cout << "\n";
}
