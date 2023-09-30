#ifndef COMMANDS_EXE_HPP
#define COMMANDS_EXE_HPP

#include "data-types.hpp"
#include "commands.hpp"

namespace turkin
{
  struct Execute
  {
    public:
      Execute();
      std::ostream & operator()(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);
    private:
      commands_dict_t dict_;
  };
}

#endif
