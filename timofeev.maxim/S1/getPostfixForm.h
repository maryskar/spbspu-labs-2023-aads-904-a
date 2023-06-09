#ifndef GETPOSTFIXFORM_H
#define GETPOSTFIXFORM_H
#include <string>
#include "queue.h"
#include "stack.h"
namespace timofeev
{
    Queue<std::string> getPostfixForm(std::string infix);
}
#endif