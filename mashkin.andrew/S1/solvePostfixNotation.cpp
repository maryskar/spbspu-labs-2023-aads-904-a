#include "solvePostfixNotation.h"
#include <stdexcept>
#include "list.h"
#include "queue.h"

void setCorrectlyEndList(mashkin::list_t< char >* list, mashkin::list_t< char >* endList)
{
  if (endList != list)
  {
    endList = list;
    while (endList->next->next)
    {
      endList = endList->next;
    }
  }
}

void deleteSomeElem(mashkin::list_t< char >* endList)
{
  delete endList->next->next;
  delete endList->next;
  endList->next = nullptr;
}

char mashkin::solvePostfixNotation(Queue< char >& que)
{
  list_t< char >* list = new list_t< char >{que.drop(), nullptr};
  list_t< char >* endList = list;
  if (que.isEmpty())
  {
    endList->next = new list_t< char >{que.drop(), nullptr};
    if (que.isEmpty())
    {
      endList->next->next = new list_t< char >{que.drop(), nullptr};
    }
    else
    {
      throw std::logic_error("Not enough arguments");
    }
  }
  else
  {
    throw std::logic_error("Not enough arguments");
  }
  if (que.isEmpty())
  {
    while (que.isEmpty())
    {
      if (endList->next->next->data == '+')
      {
        int firstNum = endList->data - '0';
        int secondNum = endList->next->data - '0';
        endList->data = firstNum + secondNum + '0';
        deleteSomeElem(endList);
        setCorrectlyEndList(list, endList);
      }
      else if (endList->next->next->data == '-')
      {
        int firstNum = endList->data - '0';
        int secondNum = endList->next->data - '0';
        endList->data = firstNum - secondNum + '0';
        deleteSomeElem(endList);
        setCorrectlyEndList(list, endList);
      }
      else if (endList->next->next->data == '*')
      {
        int firstNum = endList->data - '0';
        int secondNum = endList->next->data - '0';
        endList->data = firstNum * secondNum + '0';
        deleteSomeElem(endList);
        setCorrectlyEndList(list, endList);
      }
      else if (endList->next->next->data == '/')
      {
        int firstNum = endList->data - '0';
        int secondNum = endList->next->data - '0';
        endList->data = firstNum / secondNum + '0';
        deleteSomeElem(endList);
        setCorrectlyEndList(list, endList);
      }
      else if (endList->next->next->data == '%')
      {
        int firstNum = endList->data - '0';
        int secondNum = endList->next->data - '0';
        endList->data = firstNum % secondNum + '0';
        deleteSomeElem(endList);
        setCorrectlyEndList(list, endList);
      }
      endList = endList->next;
      endList->next->next = new list_t< char >{que.drop(), nullptr};
    }
  }
  else
  {
    if (endList->next->next->data == '+')
    {
      int firstNum = endList->data - '0';
      int secondNum = endList->next->data - '0';
      endList->data = firstNum + secondNum + '0';
      deleteSomeElem(endList);
      setCorrectlyEndList(list, endList);
    }
    else if (endList->next->next->data == '-')
    {
      int firstNum = endList->data - '0';
      int secondNum = endList->next->data - '0';
      endList->data = firstNum - secondNum + '0';
      deleteSomeElem(endList);
      setCorrectlyEndList(list, endList);
    }
    else if (endList->next->next->data == '*')
    {
      int firstNum = endList->data - '0';
      int secondNum = endList->next->data - '0';
      endList->data = firstNum * secondNum + '0';
      deleteSomeElem(endList);
      setCorrectlyEndList(list, endList);
    }
    else if (endList->next->next->data == '/')
    {
      int firstNum = endList->data - '0';
      int secondNum = endList->next->data - '0';
      endList->data = firstNum / secondNum + '0';
      deleteSomeElem(endList);
      setCorrectlyEndList(list, endList);
    }
    else if (endList->next->next->data == '%')
    {
      int firstNum = endList->data - '0';
      int secondNum = endList->next->data - '0';
      endList->data = firstNum % secondNum + '0';
      deleteSomeElem(endList);
      setCorrectlyEndList(list, endList);
    }
  }
  return list->data;
}
