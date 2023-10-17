#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <AVL.h>
#include <outputOfSpecialMessages.h>
#include "traverseCommands.h"
#include "keyValueSummator.h"

int main(int argc, char** argv)
{
  using dictionary = dmitriev::AVL< const int, std::string >;
  using summator = dmitriev::KeyValueSummator;
  using command = summator(*)(const dictionary&, summator);


  if (argc != 3)
  {
    std::cout << "incorrect argc count" << '\n';
    return 1;
  }
  std::ifstream file(argv[2]);
  if (!file.is_open())
  {
    std::cout << "problems with opening file" << '\n';
    return 1;
  }

  long key;
  std::string value;
  dictionary dict;

  try
  {
    while (file >> key >> value)
    {
      if (key > std::numeric_limits< int >::max())
      {
        throw std::overflow_error("overflow");
      }
      else if (key < std::numeric_limits< int >::min())
      {
        throw std::underflow_error("underflow");
      }

      dict.insert({static_cast< int >(key), value});
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  if (dict.isEmpty())
  {
    dmitriev::outOfEmptyDataMsg(std::cout) << '\n';
    return 0;
  }


  dmitriev::AVL< std::string, command > cmds;
  cmds["ascending"] = dmitriev::doAscending;
  cmds["descending"] = dmitriev::doDescending;
  cmds["breadth"] = dmitriev::doBreadth;

  try
  {
    summator res = cmds.at(argv[1])(dict, summator());
    std::cout << res.resultNumber;
    std::cout << res.resultStr;
    std::cout << '\n';
  }
  catch (const std::exception&)
  {
    std::cerr << "invalid tryverse" << '\n';
    return 1;
  }

  return 0;
}
