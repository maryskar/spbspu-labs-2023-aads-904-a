#include "commands-exe.hpp"

#include <stdexcept>

turkin::Execute::Execute():
  dict_()
{
  dict_.insert("NEW-PHRASE", new_phrase);
  dict_.insert("NEW-ENCODING", new_encoding);
  dict_.insert("NEW-MERGE", new_merge);
  
  dict_.insert("GET-PHRASE", get_phrase);
  dict_.insert("GET-ENCODING", get_encoding);
  dict_.insert("GET-FULL", get_full);
  
  dict_.insert("DEL-PHRASE", del_phrase);
  dict_.insert("DEL-ENCODING", del_encoding);
  
  dict_.insert("RE-ENCODING", re_encoding);
  
  dict_.insert("INFO-PHRASE", info_phrase);
  dict_.insert("INFO-STATE", info_state);
  dict_.insert("INFO-ALGORITHM", info_algorithm);
  
  dict_.insert("SAVE-PHRASE", save_phrase);
  dict_.insert("SAVE-FULL", save_full);
  
  dict_.insert("HELP", help);
}

std::ostream & turkin::Execute::operator()(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  if (!in)
  {
    return out;
  }
  return dict_.at(type)(p_dict, e_dict, in, out);
}
