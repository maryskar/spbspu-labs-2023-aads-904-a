#include "calculator.h"
#include "mathExprPtr.h"
#include "queue.h"
#include "stack.h"

namespace
{
  dmitriev::Queue< dmitriev::MathExprPtr > getQueueFromInput(std::string stringInp)
  {
    dmitriev::Queue< dmitriev::MathExprPtr > infQueue;
    std::string delimiter = " ";
    std::string token = "";
    size_t pos = 0;

    while ((pos = stringInp.find(delimiter)) != std::string::npos)
    {
      token = stringInp.substr(0, pos);
      infQueue.push(dmitriev::MathExprPtr(token));
      stringInp.erase(0, pos + delimiter.length());
    }
    infQueue.push(dmitriev::MathExprPtr(stringInp));

    return infQueue;
  }

  void calculate(dmitriev::Stack< long long >& postStack, dmitriev::MathExprPtr& oper)
  {
    long long n1 = postStack.getTopData();
    postStack.popBack();
    long long n2 = postStack.getTopData();
    postStack.popBack();

    postStack.push(oper->operator()(n1, n2));
  }
}

long long dmitriev::calculateTheExpression(std::string stringInp)
{
  dmitriev::Stack< dmitriev::MathExprPtr > intermStack;
  dmitriev::Queue< dmitriev::MathExprPtr > infQueue;
  dmitriev::Stack< long long > postStack;

  infQueue = getQueueFromInput(stringInp);

  while(!infQueue.isEmpty())
  {
    dmitriev::MathExprPtr infVal = std::move(infQueue.getTopData());
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
          dmitriev::MathExprPtr stackVal = std::move(intermStack.getTopData());
          intermStack.popBack();

          if (stackVal->isParenthesis())
          {
            break;
          }
          calculate(postStack, stackVal);
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
      dmitriev::MathExprPtr stackVal = std::move(intermStack.getTopData());
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
        calculate(postStack, stackVal);
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
    dmitriev::MathExprPtr stackVal = std::move(intermStack.getTopData());
    intermStack.popBack();

    if (stackVal->isParenthesis())
    {
      throw std::logic_error("logic_error");
    }

    calculate(postStack, stackVal);
  }

  return postStack.getTopData();
}
