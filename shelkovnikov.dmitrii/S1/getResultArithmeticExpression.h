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
      if (p.isDigit)
      {
        remains.push(p);
      }
      else
      {
        dsk::PartOfArithmeticExpression p2 = remains.last();
        dsk::PartOfArithmeticExpression p1 = remains.last();
        remains.push(dsk::PartOfArithmeticExpression(details::getResult(p1.element.operand_, p2.element.operand_, p.element.operator_)));
      }
    }
    return remains.last().element.operand_;
  }
}
#endif
