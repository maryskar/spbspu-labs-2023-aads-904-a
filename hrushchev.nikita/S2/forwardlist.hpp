template <typename T>
class ForwardList
{
  using value_type = T;
  using size_type = std::size_t;
  using deffirence_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
};