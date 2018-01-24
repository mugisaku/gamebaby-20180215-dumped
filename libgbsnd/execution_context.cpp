#include"libgbsnd/execution.hpp"
#include"libgbsnd/object.hpp"
#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{


enum class
evaluation_phase
{
  only_expr_evaluating,

   left_expr_evaluating,
  right_expr_evaluating,

};


struct
evaluation_frame
{
  evaluation_frame*  parent=nullptr;

  evaluation_phase  phase;

  const devices::expr*  expr;

};


struct
execution_context::
frame
{
  gbstd::string  routine_name;

  const stmt*  current;
  const stmt*      end;

  std::list<object>  object_list;

  std::vector<value>  value_stack;

  evaluation_frame*  eval_frame;

};




execution_context::
execution_context(const script&  scr) noexcept:
m_script(scr)
{
  resize(80);
}




void
execution_context::
clear() noexcept
{
  delete[] m_frame_stack          ;
           m_frame_stack = nullptr;

  m_max_number_of_frames = 0;
  m_number_of_frames     = 0;
}


void
execution_context::
resize(size_t  n) noexcept
{
  auto  new_ptr = new frame[n];

    for(int  i = 0;  i < m_number_of_frames;  ++i)
    {
      new_ptr[i] = std::move(m_frame_stack[i]);
    }


  delete[] m_frame_stack          ;
           m_frame_stack = new_ptr;

  m_max_number_of_frames = n;
}


void
execution_context::
call(gbstd::string_view  routine_name, const std::vector<value>&  argument_list) noexcept
{
  gbstd::string_copy  sc(routine_name);

    if(!test_capacity())
    {
      printf("フレームスタックがいっぱいで、%sは実行できない",sc.data());

      return;
    }


  auto  r = m_script.find_routine(routine_name);

    if(!r)
    {
      printf("%sというルーチンが見つからない",sc.data());

      return;
    }


    if(r->get_parameter_list().size() != argument_list.size())
    {
      printf("引数の数が一致しない\n");

      return;
    }


  auto&  frm = m_frame_stack[m_number_of_frames++];

  frm.routine_name = routine_name;


  auto  blk = r->get_block();

  frm.current = blk->begin();
  frm.end     = blk->end();

  frm.value_stack.clear();
  frm.object_list.clear();

  frm.eval_frame = nullptr;

  auto  arg_it = argument_list.crbegin();

    for(auto&  p: r->get_parameter_list())
    {
      frm.object_list.emplace_back(p,*arg_it++);
    }
}


const value*
execution_context::
seek_value(gbstd::string_view  name) const noexcept
{
/*
    if(m_frame_pointer)
    {
      auto  o = m_frame_pointer->find_object(name);
    }
*/

  return nullptr;
}


execution_context::result
execution_context::
run() noexcept
{
    for(;;)
    {
      auto&  frame = m_frame_stack[m_number_of_frames-1];

        if(frame.eval_frame)
        {
        }

      else
        {
            if(frame.current < frame.end)
            {
              auto&  stmt = *frame.current++;

                if(stmt.is_return())
                {
                }

              else
                if(stmt.is_expression())
                {
                  frame.eval_frame = new evaluation_frame;

                  frame.eval_frame->expr = &stmt.get_expr();
                }
            }
        }
    }
}


}}




