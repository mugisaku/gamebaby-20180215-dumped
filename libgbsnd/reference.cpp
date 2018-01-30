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




int
no_play_length(noise*  no, const int*  v)
{
    if(v)
    {
      no->set_play_length(*v);
    }


  return no->get_play_length();
}


int
no_play_length_flag(noise*  no, const int*  v)
{
    if(v)
    {
      no->set_play_length_flag(*v);
    }


  return no->test_play_length_flag();
}


int
no_keyon_flag(noise*  no, const int*  v)
{
    if(v)
    {
      no->set_keyon_flag(*v);
    }


  return no->test_keyon_flag();
}


int
no_volume(noise*  no, const int*  v)
{
    if(v)
    {
      no->set_volume(*v);
    }


  return no->get_volume();
}


int
no_shortspan_flag(noise*  no, const int*  v)
{
    if(v)
    {
      no->set_shortspan_flag(*v);
    }


  return no->test_shortspan_flag();
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

           if(name == sv("keyon_flag"                  )){return property(sq,sq_keyon_flag);}
      else if(name == sv("volume"                      )){return property(sq,sq_volume);}
      else if(name == sv("number_of_cycles_per_seconds")){return property(sq,sq_number_of_cycles_per_seconds);}
      else if(name == sv("play_length"                 )){return property(sq,sq_play_length);}
      else if(name == sv("play_length_flag"            )){return property(sq,sq_play_length_flag);}
//  else if(name == sv("")){return property();}


    }

  else
    if(obj.is_noise())
    {
      auto&  no = obj.get_noise();

           if(name == sv("keyon_flag"              )){return property(no,no_keyon_flag);}
      else if(name == sv("volume"                  )){return property(no,no_volume);}
      else if(name == sv("play_length"             )){return property(no,no_play_length);}
      else if(name == sv("play_length_flag"        )){return property(no,no_play_length_flag);}
      else if(name == sv("shortspan_flag"          )){return property(no,no_shortspan_flag);}
//  else if(name == sv("")){return property();}


    }


  auto  fn = [](void*  ptr, const int*  v)->int{return 0;};

  return property(m_pointer,fn);
}


}}




