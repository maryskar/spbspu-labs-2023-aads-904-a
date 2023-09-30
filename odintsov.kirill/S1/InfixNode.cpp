#include "InfixNode.hpp"

#include <stdexcept>

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

  Impl(long long operand):
    pnPtr(new PostfixNode(operand)),
    tag(Tag::Operand)
  {}

  Impl(const Operator& oper):
    pnPtr(new PostfixNode(oper)),
    tag(Tag::Operator)
  {}

  Impl(char chr):
    pnPtr(nullptr),
    tag(chr == '(' ? Tag::OpenParen : Tag::CloseParen)
  {
    if (chr != '(' && chr != ')') {
      pnPtr = new PostfixNode(Operator(chr));
      tag = Tag::Operator;
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

odintsov::InfixNode::InfixNode(long long operand):
  pImpl_(new Impl(operand))
{}

odintsov::InfixNode::InfixNode(const odintsov::Operator& oper):
  pImpl_(new Impl(oper))
{}

odintsov::InfixNode::InfixNode(char chr):
  pImpl_(new Impl(chr))
{}

odintsov::InfixNode::~InfixNode()
{
  delete pImpl_;
}

long long odintsov::InfixNode::getOperand() const
{
  if (!isOperand()) {
    throw std::logic_error("Invalid attempt to interpret node as operand");
  }
  return pImpl_->pnPtr->unsafeGetOperand();
}

odintsov::Operator& odintsov::InfixNode::getOperator()
{
  return const_cast< odintsov::Operator& >(const_cast< const odintsov::InfixNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::InfixNode::getOperator() const
{
  if (!isOperator()) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return pImpl_->pnPtr->unsafeGetOperator();
}

odintsov::InfixNode::Tag odintsov::InfixNode::getTag() const
{
  return pImpl_->tag;
}

bool odintsov::InfixNode::isOperator() const
{
  return getTag() == Tag::Operator;
}

bool odintsov::InfixNode::isOperand() const
{
  return getTag() == Tag::Operand;
}

bool odintsov::InfixNode::isOpenParen() const
{
  return getTag() == Tag::OpenParen;
}

bool odintsov::InfixNode::isCloseParen() const
{
  return getTag() == Tag::CloseParen;
}
