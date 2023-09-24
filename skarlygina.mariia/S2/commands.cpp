#include "commands.h"
#include <iostream>
#include <stdexcept>

std::ostream& skarlygina::print(std::ostream&, const std::string&, const Dictis&);
skarlygina::Dictionary< int, std::string > skarlygina::complement(const std::string&, const std::string&, const Dictis&);
skarlygina::Dictionary< int, std::string > skarlygina::intersect(const std::string&, const std::string&, const Dictis&);
skarlygina::Dictionary< int, std::string > skarlygina::unite(const std::string&, const std::string&, const Dictis&);
