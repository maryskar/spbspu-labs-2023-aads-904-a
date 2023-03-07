#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "partOfArithmeticExpression.h"
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
  std::string element;
  dsk::Stack< dsk::PartOfArithmeticExpression > answer;
  while (std::cin)
  {
    std::getline(std::cin, element);
    if (!std::cin)
    {
      break;
    }
    if (element.find_first_not_of(" \n") == std::string::npos)
    {
      continue;
    }
    try
    {
      dsk::Queue< dsk::PartOfArithmeticExpression > data = dsk::getQueueOfArithmeticExpression(element);
      dsk::Queue< dsk::PartOfArithmeticExpression > polandExpression = dsk::getPolandArithmeticExpression(data);
      answer.push(dsk::PartOfArithmeticExpression(dsk::getResultArithmeticExpression(polandExpression)));
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
