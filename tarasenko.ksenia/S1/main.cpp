#include <iostream>
#include <string>
#include <cctype>
#include "fstream"
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "chartoint.h"
#include "getpriority.h"
#include "calculate.h"

std::ostream& operator<<(std::ostream& out, Elem e)
{
  if (e.is_int) return out << e.union_elem.operand;
  else return out << e.union_elem.operation;
}

int main(int argc, char *argv[])
{
  Elem elem;
  Queue<Elem> q_infix;
  Stack<Elem> s;
  std::string str = "";
  std::fstream input(argv[1]);
  // строка -> очередь(инфикс)
  while(std::getline(input,str))
  {
    size_t i = 0;
    while (i < str.size())
    {
      if (!std::isspace(str[i]))
      {
        std::string digit = "";
        if (!std::isdigit(str[i]))
        {
          elem.union_elem.operation = str[i];
          elem.is_int = false;
          i++;
        }
        else
        {
          do
          {
            digit += str[i];
            i++;
          }
          while (std::isdigit(str[i]));
          elem.union_elem.operand = std::stoi(digit);
          elem.is_int = true;
        }
        q_infix.push(elem);
      }
      else
      {
        i++;
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
          while (!s.isEmpty() && (getPriority(elem.union_elem.operation) <= getPriority(s.getTopElem().union_elem.operation)))
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
  //
  /*
  while (!q_postfix.isEmpty())
  {
    std::cout << q_postfix.drop();
  }
  std::cout << "\n";*/
  // (с помощью стека) вычисляем результат
  while (!q_postfix.isEmpty())
  {
    elem = q_postfix.drop();
    std::cout << elem << "\n";
    if (elem.is_int)
    {
      std::cout << elem << "stack\n";
      s.push(elem);
    }
    else
    {
      if (!s.isEmpty())
      {
        Elem res{true, 0};
        int b = s.drop().union_elem.operand;
        int a = s.drop().union_elem.operand;
        try
        {
          res.union_elem.operand = calculate< int >(a, b, elem.union_elem.operation);
          s.push(res);
          std::cout << res << "stack\n";
        }
        catch (const std::exception& e)
        {
          std::cout << e.what() << "\n";
        }
      }
    }
  }
  // выводим результат
  std::cout << s.drop().union_elem.operand << "\n";
}
