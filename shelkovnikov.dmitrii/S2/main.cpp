#include <iostream>
#include <dictionary.h>
#include <labList1.h>
using dict_type = dimkashelk::Dictionary< int, std::string, std::greater< > >;
using container_type = dimkashelk::Dictionary< std::string, dict_type, std::greater< > >;
int main(int argc, char *argv[])
{
  dimkashelk::labList1< container_type, dict_type >(std::cin, std::cout, argc, argv);
  return 0;
}
