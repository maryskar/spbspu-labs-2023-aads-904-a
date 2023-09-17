#ifndef FUNC_OBJECT_HPP
#define FUNC_OBJECT_HPP

#include <string>
#include <utility>

namespace turkin
{
  class KeySum
  {
    public:
      KeySum();
      void operator()(const std::pair< int, std::string > & pair);
      int get() const;
    private:
      int sum_;
  };

  class StrSum
  {
    public:
      StrSum();
      void operator()(const std::pair< int, std::string > & pair);
      std::string get() const;
    private:
      std::string sum_;
  };
}

#endif
