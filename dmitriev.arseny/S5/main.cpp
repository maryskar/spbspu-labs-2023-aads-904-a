#include <iostream>
#include <fstream>
#include <string>
#include <AVL.h>


int main()
{
  using dictionary = dmitriev::AVL< long long, std::string >;


  if (argc != 3)
  {
    std::cout << "incorrect argc count" << '\n';
    return 1;
  }
  std::ifstream file (argv[2]);
  if (!file.is_open())
  {
    std::cout << "problems with opening file" << '\n';
    return 1;
  }


  size_t key;
  std::string value;
  dictionary dict;

  while (file >> key >> value)
  {
    dict.insert({key, value});
  }





  return 0;
}
