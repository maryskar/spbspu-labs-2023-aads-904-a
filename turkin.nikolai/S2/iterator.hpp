namespace turkin
{
  template< typename T >
  class Iterator
  {
    public:
      Iterator(T * rhs);
      T & operator++(int);
      T & operator++();
      bool operator==(const Iterator< T > & rhs);
      bool operator!=(const Iterator< T > & rhs);
      T & operator*();
    private:
      T * cur_;
  };
}

template< typename T >
turkin::Iterator< T >::Iterator(T * rhs):
   cur_(rhs)
{}

template< typename T >
T & turkin::Iterator< T >::operator++(int rhs)
{
  cur_ = cur_->next;
  return cur_->data;
}

template< typename T >
T & turkin::Iterator< T >::operator++()
{
  cur_ = cur_->next;
  return cur_->data;
}

template< typename T >
bool turkin::Iterator< T >::operator==(const Iterator< T > & rhs)
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::Iterator< T >::operator!=(const Iterator< T > & rhs)
{
  return cur_ != rhs.cur_;
}

template< typename T >
T & turkin::Iterator< T >::operator*()
{
  
}
