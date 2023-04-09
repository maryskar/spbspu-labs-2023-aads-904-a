#include "calculator.h"
#include "stack.h"
#include "queue.h"

#include <string>

size_t definePriority(std::string inp);
std::string calculate(std::string s2, std::string s1, std::string symbol);
Queue< std::string > getQueueFromInput(std::istream& input);

double calculateTheExpression(std::istream& istr)
{
  Queue< std::string > infQueue;
  Stack< std::string > postStack;
  Stack< std::string > stack;

  infQueue = getQueueFromInput(istr);



  return;
}

size_t definePriority(std::string inp)
{
  size_t priority = 0;
  if ((inp == "+") || (inp == "-"))
  {
    priority = 1;
  }
  else if (inp == "%")
  {
    priority = 2;
  }
  else if ((inp == "*") || (inp == "/"))
  {
    priority = 3;
  }

  return priority;
}

std::string calculate(std::string s2, std::string s1, std::string symbol)
{
  double p1 = std::stod(s1);
  double p2 = std::stod(s2);
  double result = 0.0;

  if (symbol == "+")
  {
    result = p2 + p1;
  }
  else if (symbol == "-")
  {
    result = p2 - p1;
  }
  else if (symbol == "*")
  {
    result = p2 * p1;
  }
  else if (symbol == "/")
  {
    result = p2 / p1;
  }
  else if (symbol == "%")
  {
    int a1 = p1;
    int a2 = p2;
    result = a2 % a1;
  }

  return std::to_string(result);
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
