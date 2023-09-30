#include "commands.h"
#include <convertToPostfixNotation.h>
#include <isLessPriority.h>
#include <queue.h>
#include <solving.h>
#include "AVL/AVL.h"
#include "AVL/tree.h"
#include "semanticTree.h"

namespace mashkin
{
  using semTree = SemanticTree< std::string >;

  bool isOperator(const std::string& symb)
  {
    return symb == "*" || symb == "+" || symb == "-" || symb == "/" || symb == "!" || symb == "^" || symb == "%";
  }

  short int defineOperation(const std::string& symb)
  {
    if (symb == "!")
    {
      return 1;
    }
    else
    {
      return 2;
    }
  }

  std::ostream& printQueue(std::ostream& out, Queue< std::string >& que)
  {
    while (que.isEmpty())
    {
      out << que.getHead();
      que.dequeue();
      if (que.isEmpty())
      {
        out << " ";
      }
    }
    return out;
  }

  void inputExpressionToTree(Queue< std::string >& que, Stack< SemanticTree< std::string >* >& stack)
  {
    while (que.isEmpty())
    {
      semTree* newNode = new semTree{que.getHead(), AVL< short int, semTree* >()};
      if (isOperator(que.getHead()))
      {
        auto operation = defineOperation(que.getHead());
        for (short int i = --operation; i >= 0; i--)
        {
          newNode->children[i] = stack.getTop();
          stack.pop();
        }
      }
      stack.push(newNode);
      que.dequeue();
    }
  }

  void addExpr(std::istream& input, MapOfExpressions& map)
  {
    Queue< std::string > que;
    std::string key;
    std::string line;
    Stack< SemanticTree< std::string >* > expression;
    input >> key;
    std::getline(input, line);
    line += " ";
    convertToPostNot(line, que);
    inputExpressionToTree(que, expression);
    map[key] = expression.getTop();
    expression.pop();
  }

  void solveNode(semTree* node)
  {
    static AVL< std::string, int long long (*)(int long long, int long long) > mapOfSolving;
    mapOfSolving["!"] = factorial;
    mapOfSolving["+"] = sum;
    mapOfSolving["-"] = minus;
    mapOfSolving["*"] = multiplicate;
    mapOfSolving["/"] = divide;
    mapOfSolving["%"] = getRemainderAfterDivision;
    mapOfSolving["^"] = exponentiate;
    if (defineOperation(node->data) == 1)
    {
      int long long var = std::stoll(node->children[0]->data);
      node->data = std::to_string(mapOfSolving[node->data](var, var));
    }
    else
    {
      int long long first = std::stoll(node->children[0]->data);
      int long long second = std::stoll(node->children[1]->data);
      node->data = std::to_string(mapOfSolving[node->data](first, second));
    }
  }

  semTree* getSimplify_impl(semTree* node, semTree* before)
  {
    if (node->children.empty())
    {
      return before;
    }
    for (short int i = 0; i < defineOperation(node->data); i++)
    {
      node = getSimplify_impl(node->children[i], node);
    }
    for (short int i = 0; i < defineOperation(node->data); i++)
    {
      if (node->children[i]->data.find_first_of("0123456789"))
      {
        return before;
      }
    }
    solveNode(node);
    node->children.clear();
    return before;
  }

  semTree* copyExpr_impl(semTree* toCopy, const semTree* tree)
  {
    if (tree->children.empty())
    {
      return toCopy;
    }
    for (short int i = 0; i < defineOperation(tree->data); i++)
    {
      toCopy->children[i] = new semTree{tree->children.at(i)->data, AVL< short int, semTree* >()};
      copyExpr_impl(toCopy->children.at(i), tree->children.at(i));
    }
    return toCopy;
  }

  semTree* copyExpr(const semTree* tree)
  {
    semTree* res = new semTree{tree->data, AVL< short int, semTree* >()};
    return copyExpr_impl(res, tree);
  }

  void simplifyExpr(std::istream& inp, MapOfExpressions& map)
  {
    std::string key;
    std::string expr;
    inp >> key;
    inp >> expr;
    map[key] = copyExpr(map[expr]);
    auto node = map[key];
    auto begin = node;
    getSimplify_impl(begin, begin);
  }

  struct Parameters
  {
    void operator()(const std::string& value)
    {
      if (value.find_first_of("0123456789!%^*-+/"))
      {
        param_.enqueue(value);
      }
    }

    Queue< std::string > param_;
  };

  template< class F >
  F traverse_lnr_impl(SemanticTree< std::string >* root, F& f)
  {
    if (!root)
    {
      return f;
    }
    for (short int i = 0; i < root->children.size(); i++)
    {
      traverse_lnr_impl(root->children[i], f);
    }
    f(root->data);
    return f;
  }

  void getParameters(std::istream& inp, MapOfExpressions& map)
  {
    std::string key;
    inp >> key;
    Parameters param;
    traverse_lnr_impl(map[key], param);
    if (!param.param_.isEmpty())
    {
      std::cout << "Expression has no parameters\n";
    }
    else
    {
      printQueue(std::cout, param.param_) << "\n";
    }
  }

  struct NewParam
  {
    void operator()(std::string& value)
    {
      if (value == param_)
      {
        value = newParam_;
      }
    }

    std::string param_;
    std::string newParam_;
  };

  void setNewExpr(std::istream& inp, MapOfExpressions& map)
  {
    std::string expr;
    std::string key;
    inp >> key;
    inp >> expr;
    NewParam newParam;
    inp >> newParam.param_;
    inp >> newParam.newParam_;
    Parameters param;
    traverse_lnr_impl(map[expr], param);
    if (param.param_.isEmpty())
    {
      std::cout << "Expression has no parameters\n";
    }
    else
    {
      map[key] = copyExpr(map[expr]);
      traverse_lnr_impl(map[key], newParam);
    }

  }

  void replaceExprTtQueue(Queue< std::string >& que, semTree* root)
  {
    if (root->children.empty())
    {
      que.enqueue(root->data);
      return;
    }
    for (short int i = 0; i < root->children.size(); i++)
    {
      if (isOperator(root->data) && isOperator(root->children[i]->data))
      {
        if (isLessPriority(root->data, root->children[i]->data))
        {
          que.enqueue("(");
          replaceExprTtQueue(que, root->children[i]);
          que.enqueue(")");
          if (i == 0)
          {
            que.enqueue(root->data);
          }
          continue;
        }
      }
      replaceExprTtQueue(que, root->children[i]);
      if (i == 0)
      {
        que.enqueue(root->data);
      }
    }
  }

  void showExpr(std::istream& inp, MapOfExpressions& map)
  {
    std::string key;
    inp >> key;
    if (map.find(key) == map.end())
    {
      std::cout << "There is no expr\n";
      return;
    }
    Queue< std::string > toPrint;
    replaceExprTtQueue(toPrint, map[key]);
    printQueue(std::cout, toPrint) << "\n";
  }
}
