#include "calculator.h"
#include "mathExpression.h"
#include "number.h"
#include "operator.h"
#include "bracket.h"
#include "stack.h"
#include "queue.h"

#include <string>

Queue< Expression* > getQueueFromInput(std::string stringInp);
void calculate(Stack< Expression* >& postStack);
bool isOperator(char inp);
bool isBracket(char inp);

long long calculateTheExpression(std::string stringInp)
{
  Queue< Expression* > infQueue;
  Stack< Expression* > postStack;
  Stack< Expression* > stack;

  infQueue = getQueueFromInput(stringInp);

  while (!infQueue.isEmpty())
  {
    if (infQueue.getTopData()->isBracket())
    {
      Bracket* br = dynamic_cast< Bracket* >(infQueue.getTopData());
      if (br->isOpen())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();
      }
      else
      {
        while (!stack.getTopData()->isBracket())
        {
          postStack.push(stack.getTopData());
          stack.popBack();

          calculate(postStack);
        }
        stack.popBack();
        infQueue.popBack();
      }
    }
    else if (infQueue.getTopData()->isOperator())
    {
      if (stack.isEmpty() || stack.getTopData()->isBracket())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();

        continue;
      }

      Operator* infOper = dynamic_cast< Operator* >(infQueue.getTopData());
      Operator* stkOper = dynamic_cast< Operator* >(stack.getTopData());

      if (infOper->getPriority() > stkOper->getPriority())
      {
        stack.push(infQueue.getTopData());
        infQueue.popBack();
      }
      else
      {
        postStack.push(stack.getTopData());
        stack.popBack();
        calculate(postStack);
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
    if (stack.getTopData()->isBracket())
    {
      throw std::logic_error("logic_error");
    }
    postStack.push(stack.getTopData());
    stack.popBack();

    calculate(postStack);
  }

  Number* result = dynamic_cast< Number* >(postStack.getTopData());
  return result->getNumber();
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

void calculate(Stack< Expression* >& postStack)
{
  Operator* oper = dynamic_cast< Operator* >(postStack.getTopData());
  postStack.popBack();
  Number* p1 = dynamic_cast< Number* >(postStack.getTopData());
  postStack.popBack();
  Number* p2 = dynamic_cast< Number* >(postStack.getTopData());
  postStack.popBack();

  postStack.push(new Number(oper->calculate(p1->getNumber(), p2->getNumber())));
}

bool isOperator(char inp)
{
  return (inp == '+') || (inp == '-') || (inp == '*') || (inp == '/') || (inp == '%');
}

bool isBracket(char inp)
{
  return (inp == '(') || (inp == ')');
}
