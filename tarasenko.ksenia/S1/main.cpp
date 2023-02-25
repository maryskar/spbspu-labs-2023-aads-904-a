#include <iostream>
#include <string>
#include "fstream"
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "calculate.h"
#include "transformStringToInfixQueue.h"
#include "transformInfixQueueToPostfix.h"
#include "calculateByPostfixQueue.h"

int main(int argc, char *argv[])
{
  std::string str = "";
  std::fstream input(argv[1]);
  while(std::getline(input,str))
  {
    Queue< Elem > q_infix = transformStringToInfixQueue< Elem >(str);
    Queue< Elem > q_postfix = transformInfixQueueToPostfix(q_infix);
    int result = calculateByPostfixQueue< Elem >(q_postfix);
    std::cout << result << "\n";
  }
}
