#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "part.h"
#include "getPolandArithmeticExpression.h"
#include "getQueueOfArithmeticExpression.h"
#include "getResultArithmeticExpression.h"
int main(int argc, char *argv[])
{
  namespace dsk = dimkashelk;
  std::ifstream in;
  if (argc == 2)
  {
    in.open(argv[1]);
    std::cin.rdbuf(in.rdbuf());
  }
  std::string element = "";
  dsk::Stack< dsk::part > answer;
  while (std::cin)
  {
    std::getline(std::cin, element);
    if (!std::cin)
    {
      break;
    }
    if (element.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
    {
      continue;
    }
    try
    {
      dsk::Queue< dsk::part > data = dsk::getQueueOfArithmeticExpression< dsk::part >(element);
      dsk::Queue< dsk::part > polandExpression = dsk::getPolandArithmeticExpression(data);
      answer.push(dsk::makePart(dsk::getResultArithmeticExpression(polandExpression)));
    }
    catch (const std::logic_error &e)
    {
      std::cout << e.what();
      return 1;
    }
  }
  if (!answer.empty())
  {
    std::cout << answer.drop().element_.operand_;
  }
  while (!answer.empty())
  {
    std::cout << " " << answer.drop().element_.operand_;
  }
  std::cout << "\n";
  return 0;
}
