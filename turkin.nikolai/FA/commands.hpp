#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <ostream>
#include <istream>

#include "phrase-struct.hpp"
#include "encoding-struct.hpp"
#include "data-types.hpp"

namespace turkin
{
  using commands_t = std::ostream & (*)(phrase_dict_t &, encoding_dict_t &, std::istream &, std::ostream &);
  using commands_dict_t = turkin::AVLtree< std::string, commands_t, std::less< > >;

  std::ostream & new_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);
  std::ostream & new_encoding(phrase_dict_t &, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);
  std::ostream & new_merge(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);

  std::ostream & get_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);
  std::ostream & get_encoding(phrase_dict_t &, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);
  std::ostream & get_full(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);

  std::ostream & del_phrase(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);
  std::ostream & del_encoding(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out);

  std::ostream & re_encoding(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);

  std::ostream & info_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);
  std::ostream & info_state(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);
  std::ostream & info_algorithm(phrase_dict_t &, encoding_dict_t &, std::istream & in, std::ostream & out);

  std::ostream & save_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);
  std::ostream & save_full(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out);

  std::ostream & help(phrase_dict_t &, encoding_dict_t &, std::istream & in, std::ostream & out);
}

#endif
