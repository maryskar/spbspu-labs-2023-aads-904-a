#ifndef SPBSPU_LABS_2023_AADS_904_A_GETQUEUEOFARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETQUEUEOFARITHMETICEXPRESSION_H
#include <string>
#include "queue.h"
#include "partOfArithmeticExpression.h"
#include "parser.h"
namespace dimkashelk
{
  Queue< PartOfArithExpr > getQueueOfArithmeticExpression(std::string element)
  {
    Parser parser(element);
    Queue< PartOfArithExpr > data;
    while (parser.hasNext())
    {
      PartOfArithExpr part(parser());
      data.push(part);
    }
    return data;
  }
}
#endif
