#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <forward_list.h>
#include "shaker.h"
#include "qsort.h"
#include "bucket.h"
#include "fill_random.h"
#include "print.h"

template< typename OutputIt, typename Compare >
std::ostream& printSorts(OutputIt first, OutputIt last, Compare comp, std::ostream& out)
{
  using value_t = typename OutputIt::value_type;
  std::list< value_t > bidir_list_1(first, last);
  std::deque< value_t > deque_1(first, last);

  tarasenko::shakerSort(bidir_list_1.begin(), bidir_list_1.end(), comp);
  tarasenko::print(bidir_list_1.begin(), bidir_list_1.end(), out) << "\n";
  tarasenko::shakerSort(deque_1.begin(), deque_1.end(), comp);
  tarasenko::print(deque_1.begin(), deque_1.end(), out) << "\n";

  tarasenko::ForwardList< value_t > forw_list_2(first, last);
  std::list< value_t > bidir_list_2(first, last);
  std::deque< value_t > deque_2(first, last);
  tarasenko::quickSort(forw_list_2.begin(), forw_list_2.end(), comp);
  tarasenko::print(forw_list_2.begin(), forw_list_2.end(), out) << "\n";
  tarasenko::quickSort(bidir_list_2.begin(), bidir_list_2.end(), comp);
  tarasenko::print(bidir_list_2.begin(), bidir_list_2.end(), out) << "\n";
  tarasenko::quickSort(deque_2.begin(), deque_2.end(), comp);
  tarasenko::print(deque_2.begin(), deque_2.end(), out) << "\n";

  tarasenko::ForwardList< value_t > forw_list_3(first, last);
  std::list< value_t > bidir_list_3(first, last);
  std::deque< value_t > deque_3(first, last);
  tarasenko::bucketSort(forw_list_3.begin(), forw_list_3.end(), comp);
  tarasenko::print(forw_list_3.begin(), forw_list_3.end(), out) << "\n";
  tarasenko::bucketSort(bidir_list_3.begin(), bidir_list_3.end(), comp);
  tarasenko::print(bidir_list_3.begin(), bidir_list_3.end(), out) << "\n";
  tarasenko::bucketSort(deque_3.begin(), deque_3.end(), comp);
  tarasenko::print(deque_3.begin(), deque_3.end(), out) << "\n";

  return out;
}

void callCommand(const std::string& direct, const std::string& value_type, const std::string& size, std::ostream& out)
{
  auto num_of_val = std::stoll(size);
  std::string command = direct + " " + value_type;
  if (command == "ascending ints")
  {
    std::list< int > data;
    tarasenko::fillRandom(data, num_of_val);
    printSorts(data.begin(), data.end(), std::less<>{}, out);
  }
  else if (command == "descending ints")
  {
    std::list< int > data;
    tarasenko::fillRandom(data, num_of_val);
    printSorts(data.begin(), data.end(), std::greater<>{}, out);
  }
  else if (command == "ascending floats")
  {
    std::list< float > data;
    tarasenko::fillRandom(data, num_of_val);
    printSorts(data.begin(), data.end(), std::less<>{}, out);
  }
  else if (command == "descending floats")
  {
    std::list< float > data;
    tarasenko::fillRandom(data, num_of_val);
    printSorts(data.begin(), data.end(), std::greater<>{}, out);
  }
  else
  {
    throw std::invalid_argument("incorrect data for the command");
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  try
  {
    callCommand(argv[1], argv[2], argv[3], std::cout);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
}
