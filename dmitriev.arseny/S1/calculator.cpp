#include "calculator.h"
#include "stack.h"
#include "queue.h"

#include <string>

Queue< std::string > getQueueFromInput(std::istream& input);

double calculateTheExpression(std::istream& in)
{


  return;
}

Queue< std::string > getQueueFromInput(std::istream& istr)
{
  Queue< std::string > infQueue;
  std::string inp = "";
  std::string curr = "";

  std::getline(istr, inp);
  for (size_t i = 0; inp[i] != '\0'; i++)
  {
    if (inp[i] == ' ')
    {
      infQueue.push(curr);
      curr = "";
    }
    else
    {
      curr = curr + inp[i];
    }
  }
  infQueue.push(curr);

  return infQueue;
}
