#ifndef SPBSPU_LABS_2023_AADS_904_A_GETQUEUEOFARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETQUEUEOFARITHMETICEXPRESSION_H
#include <string>
#include "queue.h"
#include "part.h"
#include "parser.h"
namespace dimkashelk
{
  Queue< part > getQueueOfArithmeticExpression(std::string element)
  {
    Parser parser(element);
    Queue< part > data;
    while (parser.hasNext())
    {
      data.push(makePart(parser()));
    }
    return data;
  }
}
#endif
