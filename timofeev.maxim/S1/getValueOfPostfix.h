#ifndef GETVALUEOFPOSTFIX_H
#define GETVALUEOFPOSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"
namespace timofeev
{
    long long getValueOfPostfix(Queue< std::string >& postfix);
    //Stack <std::string> getValueOfPostfix(Queue< std::string >& postfix, Stack< std::string >& result);
}
#endif