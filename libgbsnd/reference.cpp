#include"libgbsnd/object.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




namespace{
int
sq_number_of_cycles_per_seconds(square_wave*  sq, const int*  v)
{
    if(v)
    {
      sq->set_number_of_cycles_per_seconds(*v);
    }


  return sq->get_number_of_cycles_per_seconds();
}


int
sq_play_length(square_wave*  sq, const int*  v)
{
    if(v)
    {
      sq->set_play_length(*v);
    }


  return sq->get_play_length();
}


int
sq_play_length_flag(square_wave*  sq, const int*  v)
{
    if(v)
    {
      sq->set_play_length_flag(*v);
    }


  return sq->test_play_length_flag();
}


int
sq_keyon_flag(square_wave*  sq, const int*  v)
{
    if(v)
    {
      sq->set_keyon_flag(*v);
    }


  return sq->test_keyon_flag();
}


int
sq_volume(square_wave*  sq, const int*  v)
{
    if(v)
    {
      sq->set_volume(*v);
    }


  return sq->get_volume();
}
}


property
reference::
get_property(const identifier&  id) const noexcept
{
  auto&  obj = *m_pointer;

  using sv = gbstd::string_view;

  auto  name = id.view();

    if(obj.is_square_wave())
    {
      auto&  sq = obj.get_square_wave();

           if(name == sv("keyon_flag"                  )){return property(&sq,sq_keyon_flag);}
      else if(name == sv("volume"                      )){return property(&sq,sq_volume);}
      else if(name == sv("number_of_cycles_per_seconds")){return property(&sq,sq_number_of_cycles_per_seconds);}
      else if(name == sv("play_length"                 )){return property(&sq,sq_play_length);}
      else if(name == sv("play_length_flag"            )){return property(&sq,sq_play_length_flag);}
//  else if(name == sv("")){return property();}


    }


  auto  fn = [](void*  ptr, const int*  v)->int{return 0;};

  return property(m_pointer,fn);
}


}}




