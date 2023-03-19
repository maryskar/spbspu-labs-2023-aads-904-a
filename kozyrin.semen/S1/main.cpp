#include <iostream>
#include <string>
#include <datastructures.h>

int main()
{
  std::string str = "";
  std::cin >> str;
  int num = 0;
  Queue< int > queue = Queue< int >();
  while (true) {
    std::cin >> str;
    std::cin >> num;
    if (str == "drop") {
      std::cout << queue.drop();
      continue;
    }
    queue.push(num);
  }
}