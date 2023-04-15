#include "printRezult.h"
#include "calculator.h"
#include "stack.h"

#include <string>

void printSeriesOfNumbers(std::istream& streamInp, std::ostream& streamOut)
{
  Stack< long long > arr;
  std::string stringInp = "";

  while (streamInp)
  {
    std::getline(streamInp, stringInp);
    if (!streamInp)
    {
      break;
    }
    if (stringInp.find_first_not_of(" \n") == std::string::npos)
    {
      continue;
    }
    arr.push(calculateTheExpression(stringInp));
  }

  if (!arr.isEmpty())
  {
    streamOut << arr.getTopData();
    arr.popBack();
  }
  while (!arr.isEmpty())
  {
    streamOut << ' ' << arr.getTopData();
    arr.popBack();
  }
  streamOut << '\n';
}
