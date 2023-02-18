#include <iostream>
#include <string>
#include <cctype>
#include "fstream"
#include "node.h"
#include "queue.h"
#include "stack.h"

union Types
{
  int operand;
  char operation;
};

int main(int argc, char *argv[])
{
  Queue<Types> q;
  Stack<Types> s;
  std::string str = "";
  std::fstream input(argv[1]);
  // строка -> очередь(инфикс)
  // (с помощью стека) берем элементы из очереди(инфикс.) и "собираем" очередь(постфикс)
  // функция инфикс -> постфик
  // (с помощью стека) вычисляем результат
  // выводим результат
}
