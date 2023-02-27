#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
template < typename T >
void Stack< T >::push(const T &value)
{
  if (top_ == size_)
  {
    throw;
  }
  array_[++top_] = value;
}
template < typename T >
T Stack< T >::pop()
{
}
template < typename T >
void Queue< T >::push(T rhs)
{
  //if (top_ == size_) {
  //  throw;
  //}
  array_[++top_] = rhs;
  //for (int i = 0; i < top_; ++i)
  //{
  //  std::cout << array_[i];
  //}
  //std::cout << "\n";
}
void splitLine(const std::string &string)
{
  Queue< char > queue = Queue< char >();
  for (char c: string)
  {
    if (c != '\t' && c != '\n' && c != ' ')
    {
      queue.push(c);
    }
  }
}
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  Stack< std::string > stack = Stack< std::string >();
  if (argc == 2)
  {
    std::string fileIn = argv[1];
    std::fstream fileInput(fileIn);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file " << fileIn << ".\n";
      return 1;
    }
    for (std::string line; std::getline(fileInput, line);)
    {
      std::cout << line << "\n";
      splitLine(line);
      stack.push(line);
    }
  }
  else
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      std::cout << line << "\n";
      splitLine(line);
      stack.push(line);
    }
  }
  return 0;
}
