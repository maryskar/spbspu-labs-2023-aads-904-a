#include "forward_list.h"
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"
#include <iostream>

int main()
{
  kryuchkova::ForwardIterator< int > it;
  it++;
  kryuchkova::ForwardList< int > List;
  List.IsEmpty();
}