#include <iostream>
#include <cstring>

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  if (std::strcmp(argv[1], "ascending") != 0 && std::strcmp(argv[1], "descending") != 0)
  {
    std::cerr << "Incorrect first argument\n";
    return 1;
  }
  size_t num_of_elem = 0;
  try
  {
    num_of_elem = std::strtoull(argv[3], nullptr, 10);
  }
  catch (...)
  {
    std::cerr << "Incorrect third argument\n";
    return 1;
  }

  return 0;
}
