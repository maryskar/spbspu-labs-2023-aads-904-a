#include "InfixNode.hpp"

#include <stdexcept>
#include <string>

#include "InfixQueue.hpp"
#include "Operator.hpp"
#include "PostfixNode.hpp"

struct odintsov::InfixNode::Impl {
  PostfixNode* pnPtr;
  Tag tag;

  Impl(const Impl& i):
    pnPtr(nullptr),
    tag(i.tag)
  {
    if (i.pnPtr != nullptr) {
      pnPtr = new PostfixNode(*i.pnPtr);
    }
  }

  Impl(const PostfixNode& pn):
    pnPtr(new PostfixNode(pn)),
    tag(convertTag(pn.getTag()))
  {}

  Impl(const std::string& str):
    pnPtr(nullptr)
  {
    if (str.size() == 1) {
      if (str[0] == '(') {
        tag = Tag::OpenParen;
        return;
      } else if (str[0] == ')') {
        tag = Tag::CloseParen;
        return;
      }
    }
    pnPtr = new PostfixNode(str);
    tag = convertTag(pnPtr->getTag());
  }

  Impl(long long operand):
    pnPtr(new PostfixNode(operand)),
    tag(Tag::Operand)
  {}

  Impl(const odintsov::Operator& oper):
    pnPtr(new PostfixNode(oper)),
    tag(Tag::Operator)
  {}

  Impl(char paren):
    pnPtr(nullptr),
    tag(paren == '(' ? Tag::OpenParen : Tag::CloseParen)
  {
    if (paren != '(' && paren != ')') {
      throw std::invalid_argument("Incorrect parenthesis");
    }
  }

  ~Impl()
  {
    delete pnPtr;
  }

  Tag convertTag(PostfixNode::Tag tag)
  {
    switch (tag) {
    case PostfixNode::Tag::Operator:
      return InfixNode::Tag::Operator;
    case PostfixNode::Tag::Operand:
      return InfixNode::Tag::Operand;
    default:
      throw std::invalid_argument("Unknown PostfixNode tag");
    }
  }
};

odintsov::InfixNode::InfixNode(const InfixNode& in):
  pImpl_(new Impl(*in.pImpl_))
{}

odintsov::InfixNode::InfixNode(InfixNode&& in):
  pImpl_(in.pImpl_)
{
  in.pImpl_ = nullptr;
}

odintsov::InfixNode::InfixNode(const PostfixNode& pn):
  pImpl_(new Impl(pn))
{}

odintsov::InfixNode::InfixNode(const std::string& str):
  pImpl_(new Impl(str))
{}

odintsov::InfixNode::InfixNode(long long operand):
  pImpl_(new Impl(operand))
{}

odintsov::InfixNode::InfixNode(const odintsov::Operator& oper):
  pImpl_(new Impl(oper))
{}

odintsov::InfixNode::InfixNode(char paren):
  pImpl_(new Impl(paren))
{}

odintsov::InfixNode::~InfixNode()
{
  delete pImpl_;
}

long long odintsov::InfixNode::getOperand() const
{
  if (pImpl_->pnPtr == nullptr) {
    throw std::logic_error("Invalid attempt to interpret node as operand");
  }
  return pImpl_->pnPtr->getOperand();
}

odintsov::Operator& odintsov::InfixNode::getOperator()
{
  return const_cast< odintsov::Operator& >(const_cast< const odintsov::InfixNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::InfixNode::getOperator() const
{
  if (pImpl_->pnPtr == nullptr) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return pImpl_->pnPtr->getOperator();
}

odintsov::InfixNode::Tag odintsov::InfixNode::getTag() const
{
  return pImpl_->tag;
}
