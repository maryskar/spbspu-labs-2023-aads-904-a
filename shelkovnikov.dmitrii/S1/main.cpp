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
  std::basic_istream< char > *istream = std::addressof(std::cin);
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (in.is_open())
    {
      istream = std::addressof(in);
    }
    else
    {
      std::cerr << "Cannot open file";
      return 2;
    }
  }
  std::string element = "";
  dsk::Stack< dsk::part > answer;
  while (*istream)
  {
    std::getline(*istream, element);
    if (!*istream)
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
  std::cout << " " << answer.drop().operand_;
  while (!answer.empty())
  {
    std::cout << " " << answer.drop().operand_;
  }
  return 0;
}
