#include"libgbsnd/expr.hpp"
#include"libgbsnd/execution.hpp"
#include<new>


namespace gbsnd{
namespace devices{


enum class
data_kind
{
  operand,
  unary_operation,
  binary_operation,

};

struct
expr::
data
{
  size_t  reference_count=1;

  data_kind  kind;

  union data_{
    operand  o;

    unary_operation    unop;
    binary_operation  binop;

    data_(){}
   ~data_(){}
  } data;

};


expr&
expr::
operator=(operand&&  o) noexcept
{
  unrefer();

  m_data = new data;

  m_data->kind = data_kind::operand;

  new(&m_data->data) operand(std::move(o));

  return *this;
}


expr&
expr::
operator=(unary_operation&&  unop) noexcept
{
  unrefer();

  m_data = new data;

  m_data->kind = data_kind::unary_operation;

  new(&m_data->data) unary_operation(std::move(unop));

  return *this;
}


expr&
expr::
operator=(binary_operation&&  binop) noexcept
{
  unrefer();

  m_data = new data;

  m_data->kind = data_kind::binary_operation;

  new(&m_data->data) binary_operation(std::move(binop));

  return *this;
}


expr&
expr::
operator=(const expr&  rhs) noexcept
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


expr&
expr::
operator=(expr&&  rhs) noexcept
{
    if(this != &rhs)
    {
      unrefer();

      std::swap(m_data,rhs.m_data);
    }


  return *this;
}



void
expr::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->reference_count)
        {
            switch(m_data->kind)
            {
          case(data_kind::operand         ): gbstd::destruct(m_data->data.o    );break;
          case(data_kind::unary_operation ): gbstd::destruct(m_data->data.unop );break;
          case(data_kind::binary_operation): gbstd::destruct(m_data->data.binop);break;
            }


          delete m_data          ;
                 m_data = nullptr;
        }
    }
}




bool  expr::is_operand()          const noexcept{return m_data->kind == data_kind::operand;}
bool  expr::is_unary_operation()  const noexcept{return m_data->kind == data_kind::unary_operation;}
bool  expr::is_binary_operation() const noexcept{return m_data->kind == data_kind::binary_operation;}

operand&           expr::get_operand()          const noexcept{return m_data->data.o;}
unary_operation&   expr::get_unary_operation()  const noexcept{return m_data->data.unop;}
binary_operation&  expr::get_binary_operation() const noexcept{return m_data->data.binop;}




value
expr::
evaluate(const execution_context&  ctx) const noexcept
{
    switch(m_data->kind)
    {
  case(data_kind::operand):
      return m_data->data.o.evaluate(ctx);
      break;
  case(data_kind::unary_operation):
      return m_data->data.unop.evaluate(ctx);
      break;
  case(data_kind::binary_operation):
      return m_data->data.binop.evaluate(ctx);
      break;
    }


  return value();
}


void
expr::
print() const noexcept
{
  printf("(");

    switch(m_data->kind)
    {
  case(data_kind::operand):
      m_data->data.o.print();
      break;
  case(data_kind::unary_operation):
      m_data->data.unop.print();
      break;
  case(data_kind::binary_operation):
      m_data->data.binop.print();
      break;
    }


  printf(")");
}


}}




