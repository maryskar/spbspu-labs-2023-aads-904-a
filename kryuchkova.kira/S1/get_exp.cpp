#include "get_exp.h"
#include "queue.h"
#include "stack.h"
#include <string>

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < calc_data_type > & inf)
  {
    for (size_t i = 0; i < str.size(); i++)
    {
      
    }
  }
  void infixToPostfix(Queue < calc_data_type > & inf, Queue < calc_data_type > &post);
  long long getResult(Queue < calc_data_type > & post);
}