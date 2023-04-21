#include "getQueueOfArithmeticExpression.h"
#include "parser.h"
namespace
{
  bool isParenthesis(char i)
  {
    try
    {
      auto res = dimkashelk::Parenthesis(i);
      return true;
    }
    catch (...)
    {
      return false;
    }
  }
  bool isOperator(char i)
  {
    try
    {
      auto res = dimkashelk::Operator(i);
      return true;
    }
    catch (...)
    {
      return false;
    }
  }
  bool isNumber(std::string i)
  {
    try
    {
      auto res = std::stoll(i);
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
    if (isParenthesis(res[0]))
    {
      data.push(dsk::PartOfArithExpr(Parenthesis(res[0])));
    }
    else if (isOperator(res[0]))
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
