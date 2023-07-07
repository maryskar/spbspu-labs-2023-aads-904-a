#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>

template <typename T>
class ForwardList
{
  using value_type = T;
  using size_type = size_t;
  using deffirence_type = ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
};

#endif
