#include "getQueueOfArithmeticExpression.h"
#include "parser.h"
dimkashelk::Queue< dimkashelk::PartOfArithExpr > dimkashelk::getQueueOfArithmeticExpression(std::string element)
{
  namespace dsk = dimkashelk;
  dsk::Parser parser(element);
  dsk::Queue< dsk::PartOfArithExpr > data;
  while (parser.hasNext())
  {
    dsk::PartOfArithExpr part(parser());
    data.push(part);
  }
  return data;
}