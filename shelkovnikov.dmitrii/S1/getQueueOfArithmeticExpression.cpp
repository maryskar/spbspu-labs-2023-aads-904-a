#include "getQueueOfArithmeticExpression.h"
#include "parser.h"
dimkashelk::Queue< dimkashelk::PartOfArithExpr > dimkashelk::getQueueOfArithmeticExpression(std::string element)
{
  namespace dsk = dimkashelk;
  dsk::Parser parser(element);
  dsk::Queue< dsk::PartOfArithExpr > data;
  while (parser.hasNext())
  {
    std::string res = parser();
    try
    {
      data.push(dsk::PartOfArithExpr(Parenthesis(res[0])));
    }
    catch (...)
    {}
    try
    {
      data.push(dsk::PartOfArithExpr(Operator(res[0])));
    }
    catch (...)
    {}
    try
    {
      data.push(dsk::PartOfArithExpr(std::stoll(res)));
    }
    catch (...)
    {}
  }
  return data;
}
