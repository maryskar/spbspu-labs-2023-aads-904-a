#include "queue.h"
#include "stack.h"
#include "node.h"
#include "utils.h"
#include "get_exp.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <io.h>

int main(int argc, char *argv[])
{
  if (argc != 1 && argc != 2)
  {
    std::cerr  << "Not correct number of arguments for program\n";
    return 1;
  }
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cout << "Error with opening file";
      return 1;
    }
    while (!file.eof())
    {
      std::string str;
      std::getline(file, str);
      kryuchkova::Queue < char > inf;
      kryuchkova::Queue < char > post;
      kryuchkova::stringToInfix(str, inf);
      kryuchkova::infixToPostfix(inf, post);
      while (!post.isEmpty())
      {
        std::cout << post.drop();
      }
      std::cout << '\n';
    }
  }

  //int a;
  // kryuchkova::Stack <int> stack;
  // std::cin >> a;
  // stack.push(a);
  // stack.push(a + 1);
  // int b = stack.drop();
  // std::cout << b << ' ' << stack.drop() << '\n';
  // kryuchkova::Queue <kryuchkova::calc_data_type> queue;
  // kryuchkova::calc_data_type data;
  // for (int i = 0; i < 5; i++)
  // {
  //   std::cin >> data.data;
  //   queue.push(data);
  // }
  // while (!queue.isEmpty())
  // {
  //   std::cout << queue.drop() << ' ';
  // }

  // return 0;
}
