#include <iostream>
#include <string>
#include <stdexcept>
#include "sort_commands.h"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  std::string c1 = argv[1];
  std::string c2 = argv[2];
  std::string command = c1 + " " + c2;
  try
  {
    auto num_of_val = std::stoll(argv[3]);
    if (num_of_val < 1)
    {
      throw std::invalid_argument("Invalid command");
    }
    tarasenko::Commands<> commands;
    commands.at(command)(std::cout, num_of_val);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
}
