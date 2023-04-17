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
  std::string expression;
  dsk::Stack< dsk::PartOfArithExpr > answer;
  while (std::cin)
  {
    std::getline(std::cin, expression);
    if (!std::cin)
    {
      break;
    }
    if (expression.find_first_not_of(" \n") == std::string::npos)
    {
      continue;
    }
    try
    {
      dsk::Queue< dsk::PartOfArithExpr > data = dsk::getQueueOfArithmeticExpression(expression);
      dsk::Queue< dsk::PartOfArithExpr > polandExpression = dsk::getPolandArithExpr(data);
      answer.pushFront(dsk::PartOfArithExpr(dsk::getResultArithmeticExpression(polandExpression)));
    }
    catch (const std::logic_error &e)
    {
      std::cout << e.what();
      return 1;
    }
  }
  if (!answer.empty())
  {
    std::cout << answer.last().getOperand();
    answer.popFront();
  }
  while (!answer.empty())
  {
    std::cout << " " << answer.last().getOperand();
    answer.popFront();
  }
  std::cout << "\n";
  return 0;
}
