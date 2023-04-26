#include "calculator.h"
#include "mathExprPtr.h"
#include "queue.h"
#include "stack.h"

#include <string>

Queue< MathExprPtr > getQueueFromInput(std::string stringInp);
void calculate(Stack< long long >& postStack, Expression* oper);

long long calculateTheExpression(std::string stringInp)
{
  Stack< MathExprPtr > stack;
  Queue< MathExprPtr > infQueue = getQueueFromInput(stringInp);
  Stack< long long > postStack;

  while(!infQueue.isEmpty())
  {
    MathExprPtr infVal = std::move(infQueue.getTopData());
    Expression* infQAdrs = infVal.getRawPointer();

    infQueue.popBack();

    if (infQAdrs->isParenthesis())
    {
      if (infQAdrs->isOpenParenthesis())
      {
        stack.push(std::move(infVal));
      }
      else
      {
        while(!stack.isEmpty())
        {
          MathExprPtr stackVal = std::move(stack.getTopData());
          Expression* stAdrs = stackVal.getRawPointer();
          if (stAdrs->isParenthesis())
          {
            stack.popBack();
            break;
          }
          calculate(postStack, stAdrs);

          stack.popBack();
        }
      }
    }
    else if (infQAdrs->isOperator())
    {
      if (stack.isEmpty())
      {
        stack.push(std::move(infVal));
        continue;
      }
      MathExprPtr stackVal = std::move(stack.getTopData());
      Expression* stAdrs = stackVal.getRawPointer();

      if (stAdrs->isParenthesis())
      {
        stack.popBack();
        stack.push(std::move(stackVal));
        stack.push(std::move(infVal));
        continue;
      }
      if (infQAdrs->getPriority() > stAdrs->getPriority())
      {
        stack.popBack();
        stack.push(std::move(stackVal));
        stack.push(std::move(infVal));
      }
      else
      {
        calculate(postStack, stAdrs);
        stack.popBack();

        stack.push(std::move(infVal));
      }
    }
    else
    {
      postStack.push(infQAdrs->getNumber());
    }
  }

  while (!stack.isEmpty())
  {
    MathExprPtr stackVal = std::move(stack.getTopData());
    Expression* stAdrs = stackVal.getRawPointer();

    if (stAdrs->isParenthesis())
    {
      throw std::logic_error("logic_error");
    }

    calculate(postStack, stAdrs);
    stack.popBack();
  }

  return postStack.getTopData();
}

Queue< MathExprPtr > getQueueFromInput(std::string stringInp)
{
  Queue< MathExprPtr > infQueue;
  std::string curr = "";

  for (size_t i = 0; stringInp[i] != '\0'; i++)
  {
    if (stringInp[i] == ' ')
    {
      infQueue.push(MathExprPtr(curr));

      curr = "";
    }
    else
    {
      curr = curr + stringInp[i];
    }
  }
  infQueue.push(MathExprPtr(curr));

  return infQueue;
}

void calculate(Stack< long long >& postStack, Expression* oper)
{
  long long n1 = postStack.getTopData();
  postStack.popBack();
  long long n2 = postStack.getTopData();
  postStack.popBack();

  postStack.push(oper->getOper(n1, n2));
}
