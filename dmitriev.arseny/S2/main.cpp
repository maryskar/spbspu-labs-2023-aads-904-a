#include <iostream>
#include "forwardList.h"
#include <forward_list>

int main()
{
  //std::forward_list< int > f3 = {1, 2, 3, 4};
  //std::forward_list< int > f4 = {7, 8, 9};

  //f3.splice_after(f3.before_begin(), f4, f4.begin());
  //for (std::forward_list< int >::iterator it = f3.begin(); it != f3.end(); it++)
  //{
  //  std::cout << *it << '\n';
  //}
  //std::cout << '\n';


  dmitriev::ForwardList< int > f;

  f.pushFront(1);
  f.pushFront(2);
  f.pushFront(3);
  f.pushFront(4);

  dmitriev::ForwardList< int > x(f);

  std::cout << (x != f) << '\n';

  f.popFront();
  f.pushFront(5);

  std::cout << (x != f) << '\n';

  //for (dmitriev::ForwardIterator< int > it = x.begin(); it != x.end(); it++)
  //{
  //  std::cout << *it << '\n';
  //}

  //std::cout << '\n';

  //f.reverse();

  //for (dmitriev::ForwardIterator< int > it = x.begin(); it != x.end(); it++)
  //{
  //  std::cout << *it << '\n';
  //}

  //std::cout << '\n';


  return 0;
}
