#include"libgbsnd/device.hpp"


namespace gbsnd{
namespace devices{




void
square_wave::
update_parameters() noexcept
{
  constexpr int  shift_amount = 16;

    if(!m_number_of_samples_per_cycles)
    {
      return;
    }


  m_rise_time_base = m_number_of_samples_per_cycles<<shift_amount;

    switch(m_duty_ratio)
    {
  case(0): m_rise_time_base /= 8;break;
  case(1): m_rise_time_base /= 4;break;
  case(2): m_rise_time_base /= 2;break;
  case(3): m_rise_time_base  = m_rise_time_base/4*3;break;
    }


  m_rise_time_base >>= shift_amount;

  m_fall_time_base = m_number_of_samples_per_cycles-m_rise_time;


  uint32_t  rem = (m_time%m_number_of_samples_per_cycles);

    if(rem < m_rise_time_base)
    {
      m_rise_time = m_rise_time_base-rem;
    }

  else
    {
      m_rise_time =                    0;
      m_fall_time = rem-m_rise_time_base;
    }
}


void
square_wave::
set_duty_ratio(uint8_t  r) noexcept
{
  m_duty_ratio = (r%4);

  m_need_update = true;
}


void
square_wave::
modify_frequency() noexcept
{
    if(m_fm_shift_amount)
    {
        if(m_fm_wait_count)
        {
          --m_fm_wait_count;
        }


        if(!m_fm_wait_count)
        {
          m_fm_wait_count = m_fm_wait_count_source;


          auto  n = m_number_of_cycles_per_seconds;

               if(m_fm_moddir == moddir::up  ){n = n+(n>>m_fm_shift_amount);}
          else if(m_fm_moddir == moddir::down){n = n-(n>>m_fm_shift_amount);}


          set_number_of_cycles_per_seconds(n);
        }
    }
}


void
square_wave::
output(uint8_t*  begin, uint8_t*  end) noexcept
{
    if(m_need_update)
    {
      update_parameters();

      m_need_update = false;
    }


    if(!m_rise_time_base ||
       !m_fall_time_base)
    {
      return;
    }


  auto  it = begin;

  uint8_t  v = 0;

    while(it != end)
    {
REDO:
        if(test_keyon_flag())
        {
            if(m_rise_time)
            {
              v = m_volume;

                if(!--m_rise_time)
                {
                  m_fall_time = m_fall_time_base;
                }
            }

          else
            if(m_fall_time)
            {
              v = 0;

                if(!--m_fall_time)
                {
                  m_rise_time = m_rise_time_base;
                }
            }

          else
            {
              m_rise_time = m_rise_time_base;

              goto REDO;
            }
        }


      *it++ = v;

      ++m_time;

      modify_frequency();
      modify_volume();
      check_play_length();
    }
}


}}




