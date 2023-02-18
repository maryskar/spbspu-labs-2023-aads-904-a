#include <iostream>
#include <string>
#include <cctype>
#include "fstream"
#include "queue.h"
#include "stack.h"
#include "chartoint.h"

union Types
{
  int operand;
  char operation;
};

struct Elem{
  bool is_int;
  Types union_elem;
} elem;

int getPriority(char op)
{
  // ...
}

int main(int argc, char *argv[])
{
  Queue<Elem> q_infix;
  Stack<Elem> s;
  std::string str = "";
  std::fstream input(argv[1]);
  // строка -> очередь(инфикс)
  while(std::getline(input,str))
  {
    for (size_t i = 0; i < str.size(); i++)
    {
      if (!std::isspace(str[i]))
      {
        if (std::isdigit(str[i]))
        {
          elem.union_elem.operand = charToInt(str[i]);
          elem.is_int = true;
        }
        else
        {
          elem.union_elem.operation = str[i];
          elem.is_int = false;
        }
        q_infix.push(elem);
      }
    }
  }
  // (с помощью стека) берем элементы из очереди(инфикс.) и "собираем" очередь(постфикс)
  Queue<Elem> q_postfix;
  while (!q_infix.isEmpty())
  {
    elem = q_infix.drop();
    if (elem.is_int)
    {
      q_postfix.push(elem);
    }
    else
    {
      if (s.isEmpty())
      {
        s.push(elem);
      }
      else
      {
        if (elem.union_elem.operation == '(')
        {
          s.push(elem);
        }
        else if (elem.union_elem.operation == ')')
        {
          while (!s.isEmpty())
          {
            if (s.getTopElem().union_elem.operation == '(')
            {
              s.pop();
              break;
            }
            q_postfix.push(s.drop());
          }
        }
        else
        {
          while (!s.isEmpty() && (getPriority(elem.union_elem.operation) >= getPriority(s.getTopElem().union_elem.operation)))
          {
            q_postfix.push(s.drop());
          }
          s.push(elem);
        }
      }
    }
  }
  while (!s.isEmpty())
  {
    q_postfix.push(s.drop());
  }
  // (с помощью стека) вычисляем результат
  // выводим результат
}
