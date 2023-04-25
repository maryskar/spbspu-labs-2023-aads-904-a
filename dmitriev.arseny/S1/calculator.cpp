#include "calculator.h"
#include "mathExprPtr.h"
#include "queueForUniquePtr.h"
#include "stackForUniquePtr.h"

#include <string>

Queue< MathExprPtr > getQueueFromInput(std::string stringInp);
void calculate(Stack< long long >& postStack, Expression* oper);

long long calculateTheExpression(std::string stringInp)
{
  Stack< MathExprPtr > stack;
  Queue< MathExprPtr > infQueue = getQueueFromInput(stringInp);
  Stack< long long > postStack;

  for (; !infQueue.isEmpty(); infQueue.popBack())
  {
    MathExprPtr infVal = infQueue.getTopData();
    Expression* infQAdrs = infVal.getRawPointer();

    if (infQAdrs->isParenthesis())
    {
      if (infQAdrs->isOpenParenthesis())
      {
        stack.push(infVal);
      }
      else
      {
        for (; !stack.isEmpty(); stack.popBack())
        {
          MathExprPtr stackVal = stack.getTopData();
          Expression* stAdrs = stackVal.getRawPointer();
          if (stAdrs->isParenthesis())
          {
            stack.popBack();
            break;
          }
          calculate(postStack, stAdrs);
        }
      }
    }
    else if (infQAdrs->isOperator())
    {
      if (stack.isEmpty())
      {
        stack.push(infVal);
        continue;
      }
      MathExprPtr stackVal = stack.getTopData();
      Expression* stAdrs = stackVal.getRawPointer();

      if (stAdrs->isParenthesis())
      {
        stack.popBack();
        stack.push(stackVal);
        stack.push(infVal);
        continue;
      }
      if (infQAdrs->getPriority() > stAdrs->getPriority())
      {
        stack.popBack();
        stack.push(stackVal);
        stack.push(infVal);
      }
      else
      {
        calculate(postStack, stAdrs);
        stack.popBack();

        stack.push(infVal);
      }
    }
    else
    {
      postStack.push(infQAdrs->getNumber());
    }
  }

  for (; !stack.isEmpty(); stack.popBack())
  {
    MathExprPtr stackVal = stack.getTopData();
    Expression* stAdrs = stackVal.getRawPointer();

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
      MathExprPtr val(curr);
      infQueue.push(val);

      curr = "";
    }
    else
    {
      curr = curr + stringInp[i];
    }
  }
  MathExprPtr val(curr);
  infQueue.push(val);

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
