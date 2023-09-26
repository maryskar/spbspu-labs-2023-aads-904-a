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
  using pdt = phrase_dict_t;
  using edt = encoding_dict_t;

  std::ostream & new_phrase(pdt & p_dict, edt &, std::istream & in, std::ostream & out);
  std::ostream & new_encoding(pdt &, edt & e_dict, std::istream & in, std::ostream & out);
  std::ostream & new_merge(pdt & p_dict, edt &, std::istream & in, std::ostream & out);

  std::ostream & get_phrase(pdt & p_dict, edt &, std::istream & in, std::ostream & out);
  std::ostream & get_encoding(pdt &, edt & e_dict, std::istream & in, std::ostream & out);
  std::ostream & get_full(pdt & p_dict, edt & e_dict, std::istream & in, std::ostream & out);

  std::ostream & del_phrase(pdt & p_dict, edt & e_dict, std::istream & in, std::ostream & out);
  std::ostream & del_encoding(pdt & p_dict, edt & e_dict, std::istream & in, std::ostream & out);

  std::ostream & re_encoding(pdt & p_dict, edt &, std::istream & in, std::ostream & out);

  std::ostream & info_phrase(pdt & p_dict, edt &, std::istream & in, std::ostream & out);
  std::ostream & info_state(pdt & p_dict, edt &, std::istream & in, std::ostream & out);
  std::ostream & info_algorithm(pdt &, edt &, std::istream & in, std::ostream & out);

  std::ostream & save_phrase(pdt & p_dict, edt &, std::istream & in, std::ostream & out);
  std::ostream & save_full(pdt & p_dict, edt &, std::istream & in, std::ostream & out);

  std::ostream & help(pdt &, edt &, std::istream & in, std::ostream & out);
}

#endif
