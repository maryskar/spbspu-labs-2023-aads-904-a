#ifndef MASHKIN_ANDREW_SEMANTICTREE_H
#define MASHKIN_ANDREW_SEMANTICTREE_H
#include <string>
#include "AVL/AVL.h"

namespace mashkin
{
  template< class T >
  struct SemanticTree
  {
    T data;
    AVL< short int, SemanticTree< T >* > children;
  };
}
#endif
