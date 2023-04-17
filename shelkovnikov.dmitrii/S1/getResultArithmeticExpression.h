#ifndef SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETRESULTARITHMETICEXPRESSION_H
#include "queue.h"
#include "partOfArithmeticExpression.h"
namespace dimkashelk
{
  namespace details
  {
    long long getResult(long long first, long long second, dimkashelk::Operator oper);
  }
  long long getResultArithmeticExpression(Queue< PartOfArithExpr > &polandExpression);
}
#endif
