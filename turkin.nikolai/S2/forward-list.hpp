#include <oneway-list.hpp>
#include <cstddef>

namespace turkin
{
  template< typename T >
  class ForwardList
  {
    public:
      ForwardList();
      ForwardList(const ForwardList< T > & rhs);
      ForwardList(ForwardList< T > && rhs);
      ForwardList & operator=(const ForwardList< T > & rhs);
      ForwardList & operator=(ForwardList< T > && rhs);
      ~ForwardList();
      void assign(size_t count, const T & value);
template< typename T >
bool turkin::Iterator< T >::operator==(const Iterator< T > & rhs)
{
  return cur_ == rhs.cur_;
}
    private:
      OneWayNode< T > * head_;
      OneWayNode< T > * dummy_;
  };
}

template< typename T >
turkin::ForwardList< T >::ForwardList():
  head_(nullptr),
  dummy_(nullptr)
{}
