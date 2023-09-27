#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <message.h>
#include <read_trash.h>
#include "dictionary.h"
#include "funcs_for_map_commands.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class Commands
  {
   using dict_type = Dictionary< Key, Value, Compare >;
   using dict_of_dict_t = Dictionary< std::string, dict_type, std::greater<> >;
  public:
   Commands():
     type_1(),
     type_2()
   {
     type_1.push("complement", &complementCommand< Key, Value, Compare >);
     type_1.push("intersect", &intersectCommand< Key, Value, Compare >);
     type_1.push("union", &unionCommand< Key, Value, Compare >);
     type_1.push("merge", &mergeCommand< Key, Value, Compare >);
     type_1.push("add", &addCommand< Key, Value, Compare >);
     type_1.push("delete", &deleteCommand< Key, Value, Compare >);
     type_1.push("resort", &resortCommand< Key, Value, Compare >);
     type_1.push("put", &putCommand< Key, Value, Compare >);
     type_1.push("copy", &copyCommand< Key, Value, Compare >);
     type_1.push("random_dict", &randomCommand< Key, Value, Compare >);
     type_1.push("swap", &swapCommand< Key, Value, Compare >);
     type_1.push("update", &updateCommand< Key, Value, Compare >);

     type_2.push("write", &writeCommand< Key, Value, Compare >);
     type_2.push("print", &printCommand< Key, Value, Compare >);
     type_2.push("print_if", &printIfCommand< Key, Value, Compare >);
     type_2.push("subset", &subsetCommand< Key, Value, Compare >);
   }

   void call(const std::string& name_of_command, dict_of_dict_t& dict_of_dict,
      std::istream& input, std::ostream& output)
   {
     try
     {
       if (findInType1(name_of_command))
       {
         type_1.at(name_of_command)(input, dict_of_dict);
       }
       else if (findInType2(name_of_command))
       {
         type_2.at(name_of_command)(output, input, dict_of_dict);
       }
       else
       {
         throw std::out_of_range("Invalid command");
       }
     }
     catch (const std::invalid_argument& e)
     {
       output << outMessageEmpty << "\n";
       readTrash(input);
     }
     catch (const std::exception& e)
     {
       output << outMessageInvalidCommand << "\n";
       readTrash(input);
     }
   }

  private:
   using command1_t = std::function< std::istream&(std::istream&, dict_of_dict_t&) >;
   using command2_t = std::function< std::ostream&(std::ostream&, std::istream&, const dict_of_dict_t&) >;
   Dictionary< std::string, command1_t, Compare > type_1;
   Dictionary< std::string, command2_t, Compare > type_2;
   bool findInType1(const std::string& key) const;
   bool findInType2(const std::string& key) const;
  };

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType1(const std::string& key) const
  {
    return type_1.find(key) != type_1.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType2(const std::string& key) const
  {
    return type_2.find(key) != type_2.cend();
  }
}
#endif
