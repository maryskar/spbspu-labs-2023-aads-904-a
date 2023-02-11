#include <iostream>
#include <string>
#include "queue.h"
#include "parser.h"
#include "stack.h"
#include "part.h"
#include "functions.h"
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
      while (!polandExpression.empty())
      {
        dsk::part p = polandExpression.drop();
        if (p.isDigit_)
        {
          std::cout << p.operand_ << " ";
        }
        else
        {
          std::cout << p.operator_ << " ";
        }
      }
      std::cout << "\n";
    }
    catch (...)
    {}
  }
  return 0;
}
