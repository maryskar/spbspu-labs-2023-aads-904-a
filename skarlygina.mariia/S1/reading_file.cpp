#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include "list.h"

template< typename T>
List< T > readElements(std::ifstream file)
{
  std::string line;
  List< T > list = nullptr;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      size_t pos = 0;
      std::string token;
      while ((pos = line.find(" ") != std::string::npos))
      {
        token = line.substr(0, pos);
        list->data = token;
        line.erase(0, pos + 1);
      }
      //adding the last elem later
    }
    file.close();
  }
  //change list into stack or queue
  return list;
}
