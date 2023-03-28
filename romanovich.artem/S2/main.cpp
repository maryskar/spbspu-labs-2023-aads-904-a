#include <iostream>
int main(int argc, char **argv)
{
  if (argc % 2 == 1)
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  std::string dict = argv[1];
  std::cout << dict << "\n";
  for (size_t i = 2; i < argc; i+=2)
  {
    std::string key = argv[i];
    std::string value = argv[i+1];
    std::cout << key << " " << value << "\n";
  }
}