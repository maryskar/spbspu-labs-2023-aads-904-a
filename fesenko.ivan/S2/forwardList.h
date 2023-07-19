#ifndef FORWARDLIST_H
#define FORWARDLIST_H
namespace fesenko
{
  template< typename T >
  class ForwadrList
  {
   public:
    ForwardList();
    ForwardList(const ForwardList< T > &);
    ForwardList(ForwardList< T > &&);
    ForwardList< T > &operator=(const ForwardList< T > &);
    ForwardList< T > &operator=(ForwardList< T > &&);
    ~ForwardList();
  };
}
#endif
