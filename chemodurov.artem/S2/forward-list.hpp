#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>

template< typename T >
class ForwardList
{
 public:
  ForwardList();
  ForwardList(const ForwardList< T > & list);
  ForwardList(ForwardList< T > && list);
  ForwardList(std::initializer_list< T > init);
  ~ForwardList();
  ForwardList< T > & operator=(const ForwardList< T > & list);
  ForwardList< T > & operator=(ForwardList< T > && list);

};

#endif
