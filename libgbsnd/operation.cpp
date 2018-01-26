#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




enum class
operation_kind
{
  prefix_unary,
  postfix_unary,
  binary,
};


struct
operation::
data
{
  size_t  reference_count=1;

  operation_kind  kind;

  operator_word  word;

  operand   first_operand;
  operand  second_operand;

};




operation::
operation(prefix_unary_operator  op, operand&&  o) noexcept:
m_data(new data)
{
  m_data->kind = operation_kind::prefix_unary;

  m_data->word = op.word;

  m_data->first_operand = std::move(o);
}


operation::
operation(postfix_unary_operator  op, operand&&  o) noexcept:
m_data(new data)
{
  m_data->kind = operation_kind::postfix_unary;

  m_data->word = op.word;

  m_data->first_operand = std::move(o);
}


operation::
operation(binary_operator  op, operand&&  o1, operand&&  o2) noexcept:
m_data(new data)
{
  m_data->kind = operation_kind::binary;

  m_data->word = op.word;

  m_data->first_operand  = std::move(o1);
  m_data->second_operand = std::move(o2);
}




operation&
operation::
operator=(const operation&  rhs) noexcept
{
    if(this != &rhs)
    {
      unrefer();

      m_data = rhs.m_data;

        if(m_data)
        {
          ++m_data->reference_count;
        }
    }


  return *this;
}


operation&
operation::
operator=(operation&&  rhs) noexcept
{
    if(this != &rhs)
    {
      unrefer();

      std::swap(m_data,rhs.m_data);
    }


  return *this;
}




void
operation::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->reference_count)
        {
          delete m_data          ;
                 m_data = nullptr;
        }
    }
}




bool  operation::is_prefix_unary() const noexcept{return m_data->kind == operation_kind::prefix_unary;}
bool  operation::is_postfix_unary() const noexcept{return m_data->kind == operation_kind::postfix_unary;}
bool  operation::is_binary() const noexcept{return m_data->kind == operation_kind::binary;}




value
operation::
evaluate(const execution_context&  ctx) const noexcept
{
    switch(m_data->kind)
    {
  case(operation_kind::prefix_unary):
//      return devices::evaluate(m_data->word,m_data->first_operand);
      break;
  case(operation_kind::postfix_unary):
//      return devices::evaluate(m_data->first_operand,m_data->word);
      break;
  case(operation_kind::binary):
//      return devices::evaluate(m_data->first_operand,m_data->word,m_data->second_operand);
      break;
    }


  return value();
}


void
operation::
print() const noexcept
{
  short_string  ss(m_data->word);

    switch(m_data->kind)
    {
  case(operation_kind::prefix_unary):
      printf("%s",ss.data());
      m_data->first_operand.print();
      break;
  case(operation_kind::postfix_unary):
      m_data->first_operand.print();
      printf("%s",ss.data());
      break;
  case(operation_kind::binary):
      printf("(");
      m_data->first_operand.print();
      printf("%s",ss.data());
      m_data->second_operand.print();
      printf(")");
      break;
    }
}


}}




