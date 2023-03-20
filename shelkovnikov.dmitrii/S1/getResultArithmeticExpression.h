#ifndef SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#include "queue.h"
#include "partOfArithmeticExpression.h"
#include "stack.h"
#include "getResultOfArithmeticExpression.h"
namespace dimkashelk
{
  long long getResultArithmeticExpression(Queue< PartOfArithmeticExpression > &polandExpression)
  {
    namespace dsk = dimkashelk;
    dsk::Stack< dsk::PartOfArithmeticExpression > remains;
    while (!polandExpression.empty())
    {
      dsk::PartOfArithmeticExpression p = polandExpression.front();
      polandExpression.pop_front();
      if (p.isDigit)
      {
        remains.push(p);
      }
      else
      {
        dsk::PartOfArithmeticExpression p2 = remains.last();
        remains.pop_back();
        dsk::PartOfArithmeticExpression p1 = remains.last();
        remains.pop_back();
        remains.push(dsk::PartOfArithmeticExpression(details::getResult(p1.element.operand_, p2.element.operand_, p.element.operator_)));
      }
    }
    auto res = remains.last().element.operand_;
    remains.pop_back();
    return res;
  }
}
#endif
