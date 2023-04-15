#include "calculator.h"
#include "mathExpression.h"
#include "stack.h"
#include "queue.h"

#include <string>

Queue< Expression* > getQueueFromInput(std::string stringInp);

long long calculateTheExpression(std::string stringInp)
{
  Queue< std::string > infQueue;
  Stack< std::string > postStack;
  Stack< std::string > stack;

  infQueue = getQueueFromInput(stringInp);

  while (!infQueue.isEmpty())
  {
    if (infQueue.getTopData() == "(")
    {
      stack.push(drop(infQueue));
    }
    else if (infQueue.getTopData() == ")")
    {
      while (!(stack.getTopData() == "("))
      {
        postStack.push(drop(stack));
        postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
      }
      stack.popBack();
      infQueue.popBack();
    }
    else if (definePriority(infQueue.getTopData()) > 0)
    {
      if (stack.isEmpty() || (definePriority(infQueue.getTopData()) > definePriority(stack.getTopData())))
      {
        stack.push(drop(infQueue));
      }
      else
      {
        postStack.push(drop(stack));
        postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
        stack.push(drop(infQueue));
      }
    }
    else
    {
      postStack.push(drop(infQueue));
    }
  }
  while (!stack.isEmpty())
  {
    if ((stack.getTopData() == "(") || (stack.getTopData() == ")"))
    {
      throw std::logic_error("logic_error");
    }
    postStack.push(drop(stack));
    postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
  }

  return std::stoll(drop(postStack));
}



Queue< Expression* > getQueueFromInput(std::string stringInp)
{
  Queue< Expression* > infQueue;
  std::string curr = "";

  for (size_t i = 0; stringInp[i] != '\0'; i++)
  {
    if (stringInp[i] == ' ')
    {
      if (isBracket(curr[0]))
      {
        Expression* br = new Bracket(curr[0]);
        infQueue.push(br);
      }
      else if (isOperator(curr[0]))
      {
        Expression* op = new Operator(curr[0]);
        infQueue.push(op);
      }
      else
      {
        try
        {
          Expression* num = new Number(std::stoll(curr));
          infQueue.push(num);
        }
        catch (const std::exception&)
        {
          //delete?
          throw;
        }
      }

      curr = "";
    }
    else
    {
      curr = curr + stringInp[i];
    }
  }

  if (isBracket(curr[0]))
  {
    Expression* br = new Bracket(curr[0]);
    infQueue.push(br);
  }
  else if (isOperator(curr[0]))
  {
    Expression* op = new Operator(curr[0]);
    infQueue.push(op);
  }
  else
  {
    try
    {
      Expression* num = new Number(std::stoll(curr));
      infQueue.push(num);
    }
    catch (const std::exception&)
    {
      //delete?
      throw;
    }
  }

  return infQueue;
}
