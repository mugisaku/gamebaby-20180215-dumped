#include"libgbsnd/execution.hpp"
#include"libgbsnd/object.hpp"
#include"libgbsnd/stmt.hpp"
#include"libgbsnd/routine.hpp"


namespace gbsnd{
namespace devices{


struct
execution_context::
frame
{
  gbstd::string  routine_name;

  stmt_list::const_iterator    begin;
  stmt_list::const_iterator  current;
  stmt_list::const_iterator      end;

  std::list<object>  object_list;

  int  saved_value;

  bool  condition;

  devices::data_stack  data_stack;

  const expr_element*  eval_it    ;
  const expr_element*  eval_it_end;

  void  jump(gbstd::string_view  label) noexcept
  {
    auto  it = begin;

      while(it != end)
      {
          if(it->is_label() && (it->get_label() == label))
          {
            current = it;

            return;
          }


        ++it;
      }


    printf("jump error: %sというラベルが見つからない\n",label.data());
  }

};




void
execution_context::
reset(const script&  scr) noexcept
{
  m_script = scr;

  resize(80);

  m_state = state::not_ready;
}




void
execution_context::
clear() noexcept
{
  delete[] m_frame_stack          ;
           m_frame_stack = nullptr;

  m_max_number_of_frames = 0;
  m_number_of_frames     = 0;

  m_state = state::not_ready;
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

      m_state = state::not_ready;

      return;
    }


  auto  r = m_script.find_routine(routine_name);

    if(!r)
    {
      printf("%sというルーチンが見つからない",sc.data());

      m_state = state::not_ready;

      return;
    }


    if(r->get_parameter_list().size() != argument_list.size())
    {
      printf("引数の数が一致しない\n");

      m_state = state::not_ready;

      return;
    }


  auto&  frm = m_frame_stack[m_number_of_frames++];

  frm.routine_name = routine_name;


  auto&  ls = r->get_stmt_list();

  frm.begin   = ls->begin();
  frm.current = ls->begin();
  frm.end     = ls->end();

  frm.object_list.clear();

  frm.eval_it     = nullptr;
  frm.eval_it_end = nullptr;

  auto  arg_it = argument_list.crbegin();

    for(auto&  p: r->get_parameter_list())
    {
      frm.object_list.emplace_back(*arg_it++);

      frm.object_list.back().set_name(p);
    }


  m_state = state::ready;
}


value
execution_context::
get_value(gbstd::string_view  name) const noexcept
{
  auto&  frm = m_frame_stack[m_number_of_frames-1];

    for(auto&  obj: frm.object_list)
    {
        if(obj.get_name() == name)
        {
          return value(reference(obj));
        }
    }


    for(auto&  obj: m_script.get_object_list())
    {
        if(obj.get_name() == name)
        {
          return value(reference(obj));
        }
    }


  frm.object_list.emplace_back(name);

  return value(reference(frm.object_list.back()));
}


void
execution_context::
return_(value  v) noexcept
{
    if(--m_number_of_frames)
    {
      auto&  frame = m_frame_stack[m_number_of_frames-1];

      frame.data_stack.push(std::move(v));
    }
}


void
execution_context::
run(millisecond  ms) noexcept
{
    if(is_sleeping() && (m_rising_time <= ms.value))
    {
      m_state = state::ready;
    }


    if(!is_ready())
    {
      return;
    }


  constexpr size_t  count_limit = 1000;

  size_t  count = 0;

    while(m_number_of_frames)
    {
        if(++count >= count_limit)
        {
          printf("run error: カウンタ上限を越えた\n");

          break;
        }


      auto&  frame = m_frame_stack[m_number_of_frames-1];

        if(frame.eval_it)
        {
            if(frame.eval_it < frame.eval_it_end)
            {
              operate_stack(frame.data_stack,*frame.eval_it++,this);
            }

          else
            {
              auto&  stack = frame.data_stack;

              frame.eval_it = nullptr;

              auto&  stmt = *frame.current++;

                if(stmt.is_return())
                {
                  return_(stack.size()? stack.top():value());
                }

              else
                if(stmt.is_sleep())
                {
                  m_rising_time = ms.value+(stack.size()? stack.top().get_integer():0);

                  m_state = state::sleeping;

                  return;
                }

              else
                if(stmt.is_exit())
                {
                  m_returned_value = stack.size()? stack.top():value();

                  m_state = state::exited;

                  return;
                }

              else
                if(stmt.is_print())
                {
                    if(stack.size())
                    {
                      printf("PRINT: ");

                      stack.top().print();

                      printf("\n");
                    }
                }

              else
                if(stack.size())
                {
                  auto  i = stack.top().to_rhs(this).get_integer_safely();

                    if(stmt.is_evaluate_and_dump())
                    {
                    }

                  else
                    if(stmt.is_evaluate_and_save())
                    {
                      frame.saved_value = i;
                    }

                  else
                    if(stmt.is_evaluate_and_zero())
                    {
                      frame.condition = !i;
                    }

                  else
                    if(stmt.is_evaluate_and_not_zero())
                    {
                      frame.condition = i;
                    }

                  else
                    if(stmt.is_evaluate_and_equal())
                    {
                      frame.condition = (frame.saved_value == i);
                    }

                  else
                    if(stmt.is_evaluate_and_not_equal())
                    {
                      frame.condition = (frame.saved_value != i);
                    }
                }
            }
        }

      else
        if(frame.current < frame.end)
        {
          auto&  stmt = *frame.current;

            if(stmt.is_return()                ||
               stmt.is_sleep()                 ||
               stmt.is_exit()                  ||
               stmt.is_print()                 ||
               stmt.is_evaluate_and_dump()     ||
               stmt.is_evaluate_and_save()     ||
               stmt.is_evaluate_and_zero()     ||
               stmt.is_evaluate_and_not_zero() ||
               stmt.is_evaluate_and_equal()    ||
               stmt.is_evaluate_and_not_equal())
            {
              auto&  e = stmt.get_expr();

              frame.eval_it     = e.begin();
              frame.eval_it_end = e.end();

              frame.data_stack.reset();
            }

          else
            if(stmt.is_jump())
            {
              frame.jump(stmt.get_label());

              ++frame.current;
            }

          else
            if(stmt.is_jump_by_condition())
            {
                if(frame.condition)
                {
                  frame.jump(stmt.get_label());
                }


              ++frame.current;
            }

          else
            {
              ++frame.current;
            }
        }

      else
        {
          return_(value());
        }
    }


  m_state = state::exited;
}


}}




