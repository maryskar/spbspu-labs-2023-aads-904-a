#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"

int main(int argc, char *argv[])
{
  if (argc != 1 && argc != 2) {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  std::ifstream input;
  if (argc == 2) {
    input.open(argv[1]);
  }
  std::istream &in = (argc == 2) ? input : std::cin;
}
