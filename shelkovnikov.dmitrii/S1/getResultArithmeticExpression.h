#ifndef SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#include "queue.h"
#include "part.h"
#include "stack.h"
#include "functions.h"
namespace dimkashelk
{
  long long getResultArithmeticExpression(Queue< part > polandExpression)
  {
    namespace dsk = dimkashelk;
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
        remains.push(dsk::makePart(dsk::getResult(p1.element_.operand_, p2.element_.operand_, p.element_.operator_)));
      }
    }
    return remains.drop().element_.operand_;
  }
}
#endif
