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
    Expression* infAdrs = infVal.getRawPointer();
    infQueue.popBack();

    if (infAdrs->isParenthesis())
    {
      if (infAdrs->isOpenParenthesis())
      {
        stack.push(std::move(infVal));
      }
      else
      {
        while(!stack.isEmpty())
        {
          MathExprPtr stackVal = std::move(stack.getTopData());
          Expression* stAdrs = stackVal.getRawPointer();
          stack.popBack();

          if (stAdrs->isParenthesis())
          {
            break;
          }
          calculate(postStack, stAdrs);
        }
      }
    }
    else if (infAdrs->isOperator())
    {
      if (stack.isEmpty())
      {
        stack.push(std::move(infVal));
        continue;
      }
      MathExprPtr stackVal = std::move(stack.getTopData());
      Expression* stAdrs = stackVal.getRawPointer();
      stack.popBack();

      if (stAdrs->isParenthesis())
      {
        stack.push(std::move(stackVal));
        stack.push(std::move(infVal));
        continue;
      }
      if (infAdrs->getPriority() > stAdrs->getPriority())
      {
        stack.push(std::move(stackVal));
        stack.push(std::move(infVal));
      }
      else
      {
        calculate(postStack, stAdrs);
        stack.push(std::move(infVal));
      }
    }
    else
    {
      postStack.push(infAdrs->getNumber());
    }
  }

  while (!stack.isEmpty())
  {
    MathExprPtr stackVal = std::move(stack.getTopData());
    Expression* stAdrs = stackVal.getRawPointer();
    stack.popBack();
    if (stAdrs->isParenthesis())
    {
      throw std::logic_error("logic_error");
    }
    calculate(postStack, stAdrs);
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

  postStack.push(oper->operator()(n1, n2));
}
