#include <iostream>
#include <string>
#include "fstream"
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "calculate.h"
#include "transformStringToInfixQueue.h"
#include "transformInfixQueueToPostfix.h"

std::ostream& operator<<(std::ostream& out, Elem e)
{
  if (e.is_int) return out << e.union_elem.operand;
  else return out << e.union_elem.operation;
}

int main(int argc, char *argv[])
{
  Elem elem;
  std::string str = "";
  std::fstream input(argv[1]);
  while(std::getline(input,str))
  {
    Queue< Elem > q_infix = transformStringToInfixQueue< Elem >(str);
    Queue< Elem > q_postfix = transformInfixQueueToPostfix(q_infix);
    /*
    while (!q_postfix.isEmpty())
    {
      std::cout << q_postfix.drop();
    }
    std::cout << "\n";*/
    Stack< Elem > s;
    // (с помощью стека) вычисляем результат
    while (!q_postfix.isEmpty())
    {
      elem = q_postfix.drop();
      if (elem.is_int)
      {
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
  //
}
