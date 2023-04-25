#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include "queue.h"

template<typename T>
Queue< T > readElements(std::ifstream& file)
{
  std::string line;
  Stack< T > stack;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      size_t pos = 0;
      std::string token;
      while ((pos = line.find(" ")) != std::string::npos)
      {
        token = line.substr(0, pos);
        stack.push(T(token));
        line.erase(0, pos + 1);
      }
      // add last element
      stack.push(T(line));
    }
    file.close();
  }
  return stack;
}
