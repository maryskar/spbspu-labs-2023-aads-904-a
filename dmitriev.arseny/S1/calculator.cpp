#include "calculator.h"
#include "mathExprPtr.h"
#include "stack.h"
#include "queue.h"

#include <string>

Queue< ExpressionU > getQueueFromInput(std::string stringInp);

long long calculateTheExpression(std::string stringInp)
{
  Queue< ExpressionU > infQueue = getQueueFromInput(stringInp);
  Stack< ExpressionU > postStack;
  Stack< ExpressionU > stack;


  while (!infQueue.isEmpty())
  {
    if (infQueue.getTopData().isBracket())
    {
      if (infQueue.getTopData().getBracket().isOpen())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();
      }
      else
      {
        while (!stack.getTopData().isBracket())
        {
          postStack.push(stack.getTopData());
          stack.popBack();

          ExpressionU op = postStack.getTopData();
          postStack.popBack();
          ExpressionU n1 = postStack.getTopData();
          postStack.popBack();
          ExpressionU n2 = postStack.getTopData();
          postStack.popBack();

          postStack.push(op.calculate(n1, n2));
        }
        stack.popBack();
        infQueue.popBack();
      }
    }
    else if (infQueue.getTopData().isOperator())
    {
      if (stack.isEmpty() || stack.getTopData().isBracket())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();

        continue;
      }


      if (infQueue.getTopData().getOperator().getPriority() > stack.getTopData().getOperator().getPriority())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();
      }
      else
      {
        postStack.push(stack.getTopData());
        stack.popBack();

        ExpressionU op = postStack.getTopData();
        postStack.popBack();
        ExpressionU n1 = postStack.getTopData();
        postStack.popBack();
        ExpressionU n2 = postStack.getTopData();
        postStack.popBack();

        postStack.push(op.calculate(n1, n2));

        stack.push(infQueue.getTopData());
        infQueue.popBack();
      }
    }
    else
    {
      postStack.push(infQueue.getTopData());
      infQueue.popBack();
    }
  }

  while (!stack.isEmpty())
  {
    if (stack.getTopData().isBracket())
    {
      throw std::logic_error("logic_error");
    }
    postStack.push(stack.getTopData());
    stack.popBack();

    ExpressionU op = postStack.getTopData();
    postStack.popBack();
    ExpressionU n1 = postStack.getTopData();
    postStack.popBack();
    ExpressionU n2 = postStack.getTopData();
    postStack.popBack();

    postStack.push(op.calculate(n1, n2));
  }


  return postStack.getTopData().getNumber().getLongLong();
}


Queue< ExpressionU > getQueueFromInput(std::string stringInp)
{
  Queue< ExpressionU > infQueue;
  std::string curr = "";

  for (size_t i = 0; stringInp[i] != '\0'; i++)
  {
    if (stringInp[i] == ' ')
    {
      infQueue.push(curr);

      curr = "";
    }
    else
    {
      curr = curr + stringInp[i];
    }
  }
  infQueue.push(curr);

  return infQueue;
}
