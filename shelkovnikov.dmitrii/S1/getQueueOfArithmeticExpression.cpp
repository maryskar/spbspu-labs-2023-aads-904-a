#include "getQueueOfArithmeticExpression.h"
#include "parser.h"
namespace
{
  bool isNumber(std::string i)
  {
    try
    {
      std::stoll(i);
      return true;
    }
    catch (...)
    {
      return false;
    }
  }
}
dimkashelk::Queue< dimkashelk::PartOfArithExpr > dimkashelk::getQueueOfArithmeticExpression(std::string element)
{
  namespace dsk = dimkashelk;
  dsk::Parser parser(element);
  dsk::Queue< dsk::PartOfArithExpr > data;
  while (parser.hasNext())
  {
    std::string res = parser();
    if (Parenthesis::isParenthesis(res[0]))
    {
      data.push(dsk::PartOfArithExpr(Parenthesis(res[0])));
    }
    else if (Operator::isOperator(res[0]))
    {
      data.push(dsk::PartOfArithExpr(Operator(res[0])));
    }
    else if (isNumber(res))
    {
      data.push(dsk::PartOfArithExpr(std::stoll(res)));
    }
  }
  return data;
}
