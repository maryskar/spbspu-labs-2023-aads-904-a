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
      void operator()(const std::pair< long long, std::string > & pair);
      long long get() const;
    private:
      long long sum_;
  };

  class StrSum
  {
    public:
      StrSum();
      void operator()(const std::pair< long long, std::string > & pair);
      std::string get() const;
    private:
      std::string sum_;
  };
}

#endif
