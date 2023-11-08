#include "funcs_for_sort_commands.h"
#include <forward_list.h>
#include "fill_random.h"
#include "print_sorts.h"

std::ostream& tarasenko::sortAscendingInts(std::ostream& out, size_t num_of_val)
{
  tarasenko::ForwardList< int > data;
  tarasenko::fillRandom(data, num_of_val);
  return printSorts(data.begin(), data.end(), std::less<>{}, out);
}

std::ostream& tarasenko::sortDescendingInts(std::ostream& out, size_t num_of_val)
{
  tarasenko::ForwardList< int > data;
  tarasenko::fillRandom(data, num_of_val);
  return printSorts(data.begin(), data.end(), std::greater<>{}, out);
}

std::ostream& tarasenko::sortAscendingFloats(std::ostream& out, size_t num_of_val)
{
  tarasenko::ForwardList< float > data;
  tarasenko::fillRandom(data, num_of_val);
  return printSorts(data.begin(), data.end(), std::less<>{}, out);
}

std::ostream& tarasenko::sortDescendingFloats(std::ostream& out, size_t num_of_val)
{
  tarasenko::ForwardList< float > data;
  tarasenko::fillRandom(data, num_of_val);
  return printSorts(data.begin(), data.end(), std::greater<>{}, out);
}
