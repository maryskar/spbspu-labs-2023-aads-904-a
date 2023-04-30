#include "calculator.h"
#include "mathExprPtr.h"
#include "queue.h"
#include "stack.h"

Queue< MathExprPtr > getQueueFromInput(std::string stringInp);
void calculate(Stack< long long >& postStack, Expression* oper);

long long calculateTheExpression(std::string stringInp)
{
  Stack< MathExprPtr > intermStack;
  Queue< MathExprPtr > infQueue;
  Stack< long long > postStack;

  infQueue = getQueueFromInput(stringInp);

  while(!infQueue.isEmpty())
  {
    MathExprPtr infVal = std::move(infQueue.getTopData());
    infQueue.popBack();

    if (infVal->isParenthesis())
    {
      if (infVal->isOpenParenthesis())
      {
        intermStack.push(std::move(infVal));
      }
      else
      {
        while(!intermStack.isEmpty())
        {
          MathExprPtr stackVal = std::move(intermStack.getTopData());
          intermStack.popBack();

          if (stackVal->isParenthesis())
          {
            break;
          }
          calculate(postStack, *stackVal);
        }
      }
    }
    else if (infVal->isOperator())
    {
      if (intermStack.isEmpty())
      {
        intermStack.push(std::move(infVal));
        continue;
      }
      MathExprPtr stackVal = std::move(intermStack.getTopData());
      intermStack.popBack();

      if (stackVal->isParenthesis())
      {
        intermStack.push(std::move(stackVal));
        intermStack.push(std::move(infVal));
        continue;
      }
      if (infVal->operator>(*stackVal))
      {
        intermStack.push(std::move(stackVal));
        intermStack.push(std::move(infVal));
      }
      else
      {
        calculate(postStack, *stackVal);
        intermStack.push(std::move(infVal));
      }
    }
    else
    {
      postStack.push(infVal->getNumber());
    }
  }

  while (!intermStack.isEmpty())
  {
    MathExprPtr stackVal = std::move(intermStack.getTopData());
    intermStack.popBack();

    if (stackVal->isParenthesis())
    {
      throw std::logic_error("logic_error");
    }

    calculate(postStack, *stackVal);
  }

  return postStack.getTopData();
}

Queue< MathExprPtr > getQueueFromInput(std::string stringInp)
{
  Queue< MathExprPtr > infQueue;
  std::string delimiter = " ";
  size_t pos = 0;
  std::string token;

  while ((pos = stringInp.find(delimiter)) != std::string::npos)
  {
    token = stringInp.substr(0, pos);
    infQueue.push(MathExprPtr(token));
    stringInp.erase(0, pos + delimiter.length());
  }
  infQueue.push(MathExprPtr(stringInp));

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
