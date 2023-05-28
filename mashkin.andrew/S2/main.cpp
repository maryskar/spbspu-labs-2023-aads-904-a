#include <cstddef>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <iterator>
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "forwardList.h"

int main(int argc, char** argv)
{
  /*if (argc != 2)
  {
    return 1;
  }
  else
  {
  }*/
  std::forward_list< size_t > realf;
  mashkin::ForwardList< size_t > test;
  mashkin::ForwardList< size_t > test2;
  for (size_t i = 0; i < 4; ++i)
  {
    test.push_front(i);
    realf.push_front(i);
  }
  for (size_t i = 4; i < 8; ++i)
  {
    test2.push_front(i);
  }
  //mashkin::ConstIterator< size_t > citer = test.cbegin();
  //mashkin::Iterator< size_t > iter = test.begin();
  //mashkin::Iterator< size_t > last = test.begin();
  //last++;
  //last++;
  //last++;
  //last++;
  //mashkin::Iterator< size_t> before_iter = test.before_begin();
  //mashkin::ConstIterator< size_t > cend = test.cend();
  //mashkin::Iterator< size_t > end = test.end();
  //mashkin::Iterator< size_t > Iter = test.erase_after(before_iter);
  //std::forward_list< size_t >::iterator iterr = realf.erase_after(realf.cbegin());
  //realf.reverse();
  //test.reverse();
  //test.insert_after(test.cbegin(), 8);
  //test.splice_after(test.before_begin(), test2);
  //test.splice_after(test.before_begin(), test2, test2.cbegin(), ++test2.cbegin());
  realf.push_front(1);
  realf.remove(1);
  test.push_front(1);
  test.remove(1);
  for (auto it = realf.begin(); it != realf.end();)
  {
    std::cout << realf.front() << " ";
    ++it;
    realf.pop_front();
  }
  std::cout << "\n";
  for (auto it = test.begin(); it != test.end();)
  {
    std::cout << test.front() << " ";
    ++it;
    test.pop_front();
  }
  return 0;
}
