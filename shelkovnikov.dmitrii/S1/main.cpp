#include <iostream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "part.h"
#include "functions.h"
#include "getPolandArithmeticExpression.h"
#include "getQueueOfArithmeticExpression.h"
int main()
{
  namespace dsk = dimkashelk;
  std::string element = "";
  while (std::cin)
  {
    std::getline(std::cin, element);
    try
    {
      dsk::Queue< dsk::part > data = dsk::getQueueOfArithmeticExpression< dsk::part >(element);
      dsk::Queue< dsk::part > polandExpression = dsk::getPolandArithmeticExpression(data);
      dsk::Stack< dsk::part > remains;
      while (!polandExpression.empty())
      {
        dsk::part p = polandExpression.drop();
        if (p.isDigit_)
        {
          remains.push(p);
        }
        else
        {
          dsk::part p2 = remains.drop();
          dsk::part p1 = remains.drop();
          remains.push(dsk::makePart(dsk::getResult(p1.operand_, p2.operand_, p.operator_)));
        }
      }
      std::cout << remains.drop().operand_ << "\n";
    }
    catch (const std::logic_error &e)
    {
      std::cout << e.what();
      return 1;
    }
  }
  return 0;
}
