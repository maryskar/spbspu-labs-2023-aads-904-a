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

int main(int argc, char *argv[])
{
  Queue<Types> q;
  Stack<Types> s;
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
        q.push(elem.union_elem);
      }
    }
  }
  // (с помощью стека) берем элементы из очереди(инфикс.) и "собираем" очередь(постфикс)
  // функция инфикс -> постфик
  // (с помощью стека) вычисляем результат
  // выводим результат
}
